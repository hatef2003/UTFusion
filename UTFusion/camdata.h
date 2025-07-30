#ifndef CAMDATA_H
#define CAMDATA_H
#include<vector>
#define MAX_IMAGE_BOXES 16
#define IMG_LEN 640
#define IMG_WIDTH 640
class CamData
{
    uint8_t find_closest_box();
public:
    CamData();
    uint8_t len_imgboxes;
    unsigned int imgboxes[MAX_IMAGE_BOXES][4]; //TODO: change the number of bounding boxes
    float radar_img[IMG_LEN][IMG_WIDTH]; //TODO: change the image size
    float cam_img[IMG_LEN][IMG_WIDTH]; //TODO: change the image size

    void merge_images();
};

#endif // CAMDATA_H
