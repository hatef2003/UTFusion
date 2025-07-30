#ifndef CAMDATA_H
#define CAMDATA_H
#include<vector>

class CamData
{
public:
    CamData();
    int len_imgboxes;
    unsigned int imgboxes[10][4]; //TODO: change the number of bounding boxes
    float img[640][640]; //TODO: change the image size
};

#endif // CAMDATA_H
