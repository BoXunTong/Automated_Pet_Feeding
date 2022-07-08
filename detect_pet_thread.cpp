#include "detect_pet_thread.h"

Detect_pet_thread::Detect_pet_thread()
{
    // Load model
    /*model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");

    // Build the interpreter

    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

    // Get the names
    bool result = getFileContent("COCO_labels.txt");
    if(!result)
    {
        cout << "loading labels failed";
        exit(-1);
    }*/

}


void Detect_pet_thread::run()
{
    int i = 0;
    //Motor_control mMotor_control;
    while(true){
        /*if(lock_img) {
            if (frame.empty()) {
                  cout << "ERROR: Unable to grab from the camera" << endl;
                  return;
             }
            qDebug("detect_pet run....");
            detect_from_video(frame);
            msleep(100);

        }*/
        i++;
        qDebug("detect_pet run....");
        detect_from_video(frame);
        msleep(1000);
        if(i%10 == 0){
            qDebug("detect_pet callback....");
            FunB1(Motor_control::find_pets);
        }
    }


}


bool Detect_pet_thread::getFileContent(std::string fileName)
{

    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in.is_open()) return false;

    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size()>0) Labels.push_back(str);
    }
    // Close The File
    in.close();
    return true;
}


void Detect_pet_thread::detect_from_video(Mat &src)
{


    /*
    Mat image;
    //int cam_width =src.cols;
    //int cam_height=src.rows;
    bool detect_state = false;
    // copy image to input as input tensor
    cv::resize(src, image, Size(300,300));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    interpreter->SetNumThreads(2);      //quad core
    interpreter->Invoke();      // run  model

    //const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

    //there are ALWAYS 10 detections no matter how many objects are detectable

    const float confidence_threshold = 0.5;
    for(int i = 0; i < num_detections; i++)
    {
        if(detection_scores[i] > confidence_threshold)
        {
            int  det_index = (int)detection_classes[i]+1;
            if(Labels[det_index].c_str() == "dog"){
                qDebug("*************************************");
            }
            if(det_index == 18)
            {
                setFindCat(true);
                detect_state = true;
                mNum++;
                if (mNum == 2) {
                    qDebug("find a dog...");
                    mFeedCount++;
                    //setFeedCount(mFeedCount);
                }
                break;
            }
        }

    }

    if(!detect_state)
    {
        // no find pet
        setFindCat(false);
        mNum = 0;
    }

    */
}



Mat Detect_pet_thread::getMainThreadImage()
{

    return frame;
}



void Detect_pet_thread::setMainThreadImage(Mat src)
{
    lock_img = false;
    frame = src;
    lock_img = true;
}

void Detect_pet_thread::setFeedCount(int mFeed)
{
    mFeedCount = mFeed;
}
int Detect_pet_thread::getFeedCount()
{
    return mFeedCount;
}

void Detect_pet_thread::setFindCat(bool mCat)
{
    findCat = mCat;
}
bool Detect_pet_thread::getFindCat()
{
    return findCat;
}

