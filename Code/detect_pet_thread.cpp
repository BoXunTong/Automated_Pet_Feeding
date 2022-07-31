#include "detect_pet_thread.h"


Detect_pet_thread::Detect_pet_thread()
{
    // Load model
    model = tflite::FlatBufferModel::BuildFromFile("detect.tflite");

    // Build the interpreter

    tflite::InterpreterBuilder(*model.get(), resolver)(&interpreter);

    interpreter->AllocateTensors();

    // Get the names
    bool result = getFileContent("COCO_labels.txt");
    if(!result)
    {
        cout << "loading labels failed";
        exit(-1);
    }
    printf("setup Detect_pet_thread success \n");
    Motor_control::initPin();
}
 Detect_pet_thread::~Detect_pet_thread()
{
     //Threads close safely even when forcing windows to close
      requestInterruption();
      wait();
}

void Detect_pet_thread::run()
{
    while(!isInterruptionRequested()){
        time_count++;
        //starts=clock();
        if(lock_img){
            detect_from_video(frame);        
        }



        /*if(time_count % 2 == 0) {
            //cout<<"detect_pet cost time = " << (ends - starts) / 10000<< " ms" <<endl;
            time_count = 0;
        }*/

        cout << "WeightState = " << m_globalwrapper_MM << endl;
        if(m_globalwrapper_MM==1 && getFindCat()){
            callbackPet(Motor_control::motor_run);

        }else {
            callbackPet(Motor_control::motor_stop);

        }
        /*
        if(m_globalwrapper_MM==1 && getFindCat()){
            last_motor_state[1] = 1;
            if(last_motor_state[0] != last_motor_state[1]){
                callbackPet(Motor_control::motor_run);
            }
            last_motor_state[0] = 1;
        }else {
            last_motor_state[1] = 0;
            if(last_motor_state[0] != last_motor_state[1]){
                callbackPet(Motor_control::motor_stop);
            }
            last_motor_state[0] = 0;
        }*/
        msleep(1000);
        //qDebug("detect_pet endl....");
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
    starts=clock();


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
                qDebug("************************************* ");
            }
            cout<< " index = " << det_index << std::endl;
            if(det_index == 18)
            {
                setFindCat(true);
                detect_state = true;
                mNum++;
                if (mNum == 2) {
                    qDebug(" find a dog...");
                    m_globalFeedCount++;
                    //setFeedCount(mFeedCount);
                }
                ends=clock();
                cout<<"detect_pet cost time = " << (ends - starts) / 10000<< " ms" <<endl;
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
    //mFeedCount = mFeed;
}
int Detect_pet_thread::getFeedCount()
{
    return 0;
}

void Detect_pet_thread::setFindCat(bool mCat)
{
    findCat = mCat;
}
bool Detect_pet_thread::getFindCat()
{
    return findCat;
}

