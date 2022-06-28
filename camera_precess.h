#ifndef CAMERA_PRECESS_H
#define CAMERA_PRECESS_H

#include<opencv2/opencv.hpp>
using namespace cv;
class Camera_precess
{
public:
    Camera_precess();
    bool openCamera();
    Mat previewCamera();
    Mat dumpFrame();
    void releaseCamera();

private:
    VideoCapture cap;
    Mat frame;

};

#endif // CAMERA_PRECESS_H
