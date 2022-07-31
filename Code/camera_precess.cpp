#include "camera_precess.h"

Camera_precess::Camera_precess()
{

}

bool Camera_precess::openCamera()
{
    _frame = cap.open(0);

    return cap.isOpened();
}

Mat Camera_precess::previewCamera()
{
    cap.read(_frame);
    cv::resize(_frame, _frame, Size(560,390));
    cv::cvtColor(_frame, _frame, cv::COLOR_BGR2RGB);
    return _frame;
}

Mat Camera_precess::dumpFrame()
{
    Mat src = previewCamera();
    return src;
}

void Camera_precess::releaseCamera()
{

}
