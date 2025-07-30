#ifndef FUSION_H
#define FUSION_H
#include<vector>
#define MAX_IMAGE_BOXES 16
#define IMG_LEN 640
#define IMG_WIDTH 640
class Fusion
{
    void find_closest_point_in_box(uint16_t,uint16_t,uint16_t,uint16_t);
    float min_cam_distance = std::numeric_limits<float>::infinity(), min_radar_distance = std::numeric_limits<float>::infinity();
public:
    Fusion(uint8_t);
    uint8_t len_imgboxes;
    uint16_t imgboxes[MAX_IMAGE_BOXES][4]; //TODO: change the number of bounding boxes
    float radar_img[IMG_LEN][IMG_WIDTH]; //TODO: change the image size
    float cam_img[IMG_LEN][IMG_WIDTH]; //TODO: change the image size

    void merge_images();
};

#endif // FUSION_H
