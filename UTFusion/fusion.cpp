#include "fusion.h"
#include <limits>

void Fusion::find_closest_point_in_box(uint16_t ulx, uint16_t uly, uint16_t brx, uint16_t bry) // up left x and y, bottom right x and y
{
    min_cam_distance = std::numeric_limits<float>::infinity();
    min_radar_distance = std::numeric_limits<float>::infinity();

    for (int i = ulx; i < brx; i++)
        for (int j = uly; j < bry; j++)
        {
            if (cam_img[i][j] < min_cam_distance)
                min_cam_distance = cam_img[i][j];
            if (radar_img[i][j] < min_radar_distance)
                min_radar_distance = radar_img[i][j];
        }
}

Fusion::Fusion(uint8_t _len_imageboxes) {
    len_imgboxes = _len_imageboxes;
}

void Fusion::merge_images()
{
    if (len_imgboxes >= MAX_IMAGE_BOXES)
        throw 1;

        
    for (int i = 0; i < this->len_imgboxes; i++) // O(image size)*2
    {
        uint16_t ulx = this->imgboxes[i][0], uly = this->imgboxes[i][1], brx = this->imgboxes[i][2], bry = this->imgboxes[i][3];
        find_closest_point_in_box(ulx, uly, brx,bry); // O(image size)
        if (min_radar_distance < min_cam_distance) continue;

        float box_ratio = (float)min_radar_distance/(float)min_cam_distance;
        for (int i = ulx; i < brx; i++) // O(image size)
            for (int j = uly; j < bry; j++)
                if (cam_img[i][j] < min_cam_distance)
                    cam_img[i][j]*=box_ratio;
        
    }
}
