#ifndef FUSION_H
#define FUSION_H

#include "./FusionUtils/distance_calculator.h"
#include "pixel2world.h"
#include <vector>

class Fusion
{
public:
    struct PixelData {
        float pixel_depth;
        float pixel_pos_x;
        float pixel_pos_y;
        
        PixelData() = default;
        PixelData(float depth, float x, float y) 
            : pixel_depth(depth), pixel_pos_x(x), pixel_pos_y(y) {}
    };
    
    struct RadarData {
        float position_x;
        float position_y;
        float position_z;
        float output_distance;
        
        RadarData() = default;
        RadarData(float x, float y, float z, float distance)
            : position_x(x), position_y(y), position_z(z), output_distance(distance) {}
    };
    
    struct FusionOutput {
        float error;
        float pixel_pos_x;
        float pixel_pos_y;
        bool is_valid;
        
        FusionOutput() : error(std::numeric_limits<float>::max()), 
                        pixel_pos_x(0.0f), pixel_pos_y(0.0f), is_valid(false) {}
    };
    
    using ObjectVector = std::vector<std::vector<PixelData>>;

private:
    PixelToWorld m_pixelToWorld;
    std::vector<RadarData> m_radars;
    float m_epsilon;
    
public:
    explicit Fusion();
    
    void setCameraIntrinsics(const PixelToWorld::CameraIntrinsics& intrinsics);
    void setCameraPose(const PixelToWorld::CameraPose& pose);
    void setRadars(const std::vector<RadarData>& radars);
    void setEpsilon(float epsilon);
    
    /**
     * @brief Perform fusion of camera objects with radar data
     * @param objects Vector of objects, where each object is a vector of PixelData
     * @return Vector of fusion results, one per radar
     */
    std::vector<FusionOutput> performFusion(const ObjectVector& objects);
    
private:
    /**
     * @brief Find the closest radar(s) to a given world x-coordinate
     * @param world_x The x-coordinate in world space
     * @return Index of the closest radar
     */
    int findClosestRadar(float world_x);
    
    /**
     * @brief Find radar indices that bracket the given x-coordinate
     * @param world_x The x-coordinate in world space
     * @param left_radar Index of left radar (output)
     * @param right_radar Index of right radar (output)
     * @return true if bracketing radars found, false if outside range
     */
    bool findBracketingRadars(float world_x, int& left_radar, int& right_radar);
};

#endif // FUSION_H
