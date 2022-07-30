#ifndef CAMERA_PRECESS_H
#define CAMERA_PRECESS_H

#include <iostream>
#include <functional>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


typedef function<void(Mat)> CALLBACK;
class Camera_precess
{
public:
    Camera_precess();
    bool openCamera();
    Mat previewCamera();
    Mat dumpFrame();
    void releaseCamera();
    void regeditCallBack(CALLBACK fun){
        _fun = fun;
    }
    void getFrame() {
        _frame = previewCamera();
        _fun(_frame);
    }

private:
    VideoCapture cap;
    Mat _frame;
    CALLBACK _fun;

};

#endif // CAMERA_PRECESS_H
