#include "camera_thread.h"

Camera_Thread::Camera_Thread()
{
    auto Fun = bind(&Camera_Thread::callBackFun, placeholders::_1);
    mCamera_precess.openCamera();
    mCamera_precess.regeditCallBack(Fun);
}

Camera_Thread::~Camera_Thread()
{

}

void Camera_Thread::run()
{
    while(!isInterruptionRequested()){

        /*Mat frame = mCamera_precess.previewCamera();
        //msleep(1000);
        if(!frame.empty()){
            qDebug("camera thread callback....");
            setFrame(Detect_pet_thread::setMainThreadImage(frame));
            //FunB1(Motor_control::find_pets);
        }*/
        msleep(1000);
    }
}
