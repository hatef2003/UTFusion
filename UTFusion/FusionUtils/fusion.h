#ifndef FUSION_H
#define FUSION_H

#include "./FusionUtils/distance_calculator.h"
#include "pixel2world.h"
#include <vector>
#define IMG_WIDTH 100
#define IMG_HEIGHT 100
#define CAM_FX 1146.3511547076373
#define CAM_FY 1096.8692812423094
#define CAM_CX 346.74179054850418
#define CAM_CY 227.22216526982555

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
    
    std::vector<FusionOutput> performFusion(const ObjectVector& objects);
    
private:

    int findClosestRadar(float world_x);
    

    bool findBracketingRadars(float world_x, int& left_radar, int& right_radar);
};

#endif 
