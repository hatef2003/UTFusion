#include "camdata.h"
#include <limits>

uint8_t CamData::find_closest_box()
{
    float min_cam_distance = std::numeric_limits<float>::infinity(), min_radar_distance = std::numeric_limits<float>::infinity();
    for (int i = 0; i < IMG_LEN; i++)
        for (int j = 0; j < IMG_WIDTH; j++)
        {
            if (cam_img[i][j] < min_cam_distance)
                min_cam_distance = cam_img[i][j];
            if (radar_img[i][j] < min_radar_distance)
                min_radar_distance = radar_img[i][j];
        }
}

CamData::CamData() {}

void CamData::merge_images()
{
    if (len_imgboxes >= MAX_IMAGE_BOXES)
        throw 1;

    find_closest_box();
    
    for (int i = 0; i < this->len_imgboxes; i++)
    {
    }
}
