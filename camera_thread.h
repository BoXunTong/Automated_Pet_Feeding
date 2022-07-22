#ifndef CAMERA_THREAD_H
#define CAMERA_THREAD_H
#include <QThread>
#include "camera_precess.h"
#include "detect_pet_thread.h"
class Camera_Thread:public QThread
{
    Q_OBJECT
public:
    Camera_Thread();
    ~Camera_Thread();
    /* 获取到A类的图像，此时frame就是一帧数据 */
    void callBackFun(Mat frame)
    {
        cout << "B类获取到一帧数据：" << frame << endl;
    }
private:
    void run();
    void setFrame(void (*callback)()) {
        printf("I'am ProgramB.FunB1() and be called..\n");
        callback();
    }
    Camera_precess mCamera_precess;
};

#endif // CAMERA_THREAD_H
