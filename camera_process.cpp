#include "camera_precess.h"

Camera_precess::Camera_precess()
{

}

bool Camera_precess::openCamera()
{
    frame = cap.open(0);
    return cap.isOpened();
}

Mat Camera_precess::previewCamera()
{
    cap.read(frame);
    cv::resize(frame, frame, Size(560,390));
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    return frame;
}

Mat Camera_precess::dumpFrame()
{
    Mat src;
    return src;
}

void Camera_precess::releaseCamera()
{

}
