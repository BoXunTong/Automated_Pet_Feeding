#ifndef DETECT_PET_THREAD_H
#define DETECT_PET_THREAD_H
#include <QThread>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/lite/model.h"
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

class Detect_pet_thread: public QThread
{
    Q_OBJECT
public:
    Detect_pet_thread();

    void setMainThreadImage(Mat src);
    Mat getMainThreadImage();
    void setFeedCount(int mFeed);
    int getFeedCount();

    std::vector<std::string> Labels;
    std::unique_ptr<tflite::Interpreter> interpreter;
    std::unique_ptr<tflite::FlatBufferModel> model;
    tflite::ops::builtin::BuiltinOpResolver resolver;

private:
    void run();
    const size_t width = 300;
    const size_t height = 300;


    bool getFileContent(std::string fileName);
    void detect_from_video(Mat &src);

    int mFeedCount = 0;
    int mNum = 0;
    bool lock_img = false;

    Mat frame;

};

#endif // DETECT_PET_THREAD_H
