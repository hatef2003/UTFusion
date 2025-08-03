#include "fusion.h"
#include <algorithm>
#include <cmath>
#include <limits>

Fusion::Fusion()
    : m_epsilon(1.0f)
{
    PixelToWorld::CameraIntrinsics ci = PixelToWorld::CameraIntrinsics(CAM_FX, CAM_FY, CAM_CX, CAM_CY);
    this->setCameraIntrinsics(ci);
}

void Fusion::setCameraIntrinsics(const PixelToWorld::CameraIntrinsics& intrinsics)
{
    m_pixelToWorld.setCameraIntrinsics(intrinsics);
}

void Fusion::setCameraPose(const PixelToWorld::CameraPose& pose)
{
    m_pixelToWorld.setCameraPose(pose);
}

void Fusion::setRadars(const std::vector<RadarData>& radars)    // Nlog^2(N)
{
    m_radars = radars;
    std::stable_sort(m_radars.begin(), m_radars.end(),
              [](const RadarData& a, const RadarData& b) {
                  return a.position_x < b.position_x;
              });
}

void Fusion::setEpsilon(float epsilon)
{
    m_epsilon = epsilon;
}

std::vector<Fusion::FusionOutput> Fusion::performFusion(const ObjectVector& objects)
{
    std::vector<FusionOutput> output(m_radars.size());
    bool is_pixel_seen[IMG_HEIGHT][IMG_WIDTH];
    std::fill(&is_pixel_seen[0][0], &is_pixel_seen[0][0] + sizeof(is_pixel_seen) / sizeof(bool), false); // O(Nimglen)

    for (const auto& object : objects) { // O(Nimglen* (O(pixel2World) + 2Nradarlen + Nradarlen*O(logNfloatlen)))
        for (const auto& pixel : object) {
            if (is_pixel_seen[static_cast<int>(pixel.pixel_pos_y)][static_cast<int>(pixel.pixel_pos_x)])
                continue;
            else
                is_pixel_seen[static_cast<int>(pixel.pixel_pos_y)][static_cast<int>(pixel.pixel_pos_x)] = true;

            float pixel_coords[2] = {pixel.pixel_pos_x, pixel.pixel_pos_y};
            float* world_pos = m_pixelToWorld.pixelToWorld(pixel_coords, pixel.pixel_depth);
            
            if (world_pos == nullptr) continue;
            
            float world_x = world_pos[0];
            float world_y = world_pos[1];
            float world_z = world_pos[2];
            
            int left_radar, right_radar;
            std::vector<int> relevant_radars;
            
            if (findBracketingRadars(world_x, left_radar, right_radar)) {
                relevant_radars.push_back(left_radar);
                relevant_radars.push_back(right_radar);
            } else {
                int closest = findClosestRadar(world_x);
                relevant_radars.push_back(closest);
            }
            
            for (int radar_idx : relevant_radars) {
                if (radar_idx < 0 || radar_idx >= static_cast<int>(m_radars.size())) continue;
                
                const RadarData& radar = m_radars[radar_idx];
                
                float radar_pos[3] = {radar.position_x, radar.position_y, radar.position_z};
                float pixel_world_pos[3] = {world_x, world_y, world_z};
                
                float calculated_distance = DistanceCalculator::distance(pixel_world_pos, radar_pos);
                
                float error = std::abs(calculated_distance - radar.output_distance);
                
                if (error < m_epsilon && error < output[radar_idx].error) {
                    output[radar_idx].error = error;
                    output[radar_idx].pixel_pos_x = pixel.pixel_pos_x;
                    output[radar_idx].pixel_pos_y = pixel.pixel_pos_y;
                    output[radar_idx].is_valid = true;
                }
            }
            
            delete[] world_pos;
        }
    }
    
    return output;
}

int Fusion::findClosestRadar(float world_x) // O(N)
{
    if (m_radars.empty()) return -1;
    
    int closest_idx = 0;
    float min_distance = std::abs(world_x - m_radars[0].position_x);
    
    for (size_t i = 1; i < m_radars.size(); ++i) {
        float distance = std::abs(world_x - m_radars[i].position_x);
        if (distance < min_distance) {
            min_distance = distance;
            closest_idx = static_cast<int>(i);
        }
    }
    
    return closest_idx;
}

bool Fusion::findBracketingRadars(float world_x, int& left_radar, int& right_radar)
{
    if (m_radars.size() < 2) return false;

    if (world_x < m_radars.front().position_x || world_x > m_radars.back().position_x) return false;
    
    for (size_t i = 0; i < m_radars.size() - 1; ++i)
        if (world_x >= m_radars[i].position_x && world_x <= m_radars[i + 1].position_x) {
            left_radar = static_cast<int>(i);
            right_radar = static_cast<int>(i + 1);
            return true;
        }

    return false;
}
