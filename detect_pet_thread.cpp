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
}


void Detect_pet_thread::run()
{
    while(true){
        if(lock_img) {
            if (frame.empty()) {
                  cout << "ERROR: Unable to grab from the camera" << endl;
                  return;
             }
            qDebug("run detect....");
            detect_from_video(frame);
            msleep(100);
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



    Mat image;
    //int cam_width =src.cols;
    //int cam_height=src.rows;
    bool detect_state = false;
    // copy image to input as input tensor
    cv::resize(src, image, Size(300,300));
    memcpy(interpreter->typed_input_tensor<uchar>(0), image.data, image.total() * image.elemSize());

    interpreter->SetAllowFp16PrecisionForFp32(true);
    interpreter->SetNumThreads(2);      //quad core

    cout << "tensors size: " << interpreter->tensors_size() << "\n";
    cout << "nodes size: " << interpreter->nodes_size() << "\n";
    cout << "inputs: " << interpreter->inputs().size() << "\n";
    cout << "input(0) name: " << interpreter->GetInputName(0) << "\n";
    cout << "outputs: " << interpreter->outputs().size() << "\n";

    interpreter->Invoke();      // run your model

    //const float* detection_locations = interpreter->tensor(interpreter->outputs()[0])->data.f;
    const float* detection_classes=interpreter->tensor(interpreter->outputs()[1])->data.f;
    const float* detection_scores = interpreter->tensor(interpreter->outputs()[2])->data.f;
    const int num_detections = *interpreter->tensor(interpreter->outputs()[3])->data.f;

    //there are ALWAYS 10 detections no matter how many objects are detectable
//        cout << "number of detections: " << num_detections << "\n";
    printf("detecting...");
    const float confidence_threshold = 0.5;
    qDebug("num_detections = %d", num_detections);
    for(int i = 0; i < num_detections; i++)
    {
        if(detection_scores[i] > confidence_threshold)
        {
            int  det_index = (int)detection_classes[i]+1;
            qDebug(Labels[det_index].c_str());
            if(Labels[det_index].c_str() == "cat")
            {
                qDebug("find a cat");
                detect_state = true;
                mNum++;
                if (mNum == 1) {
                    mFeedCount++;
                }
                break;
            }

            /*float y1=detection_locations[4*i  ]*cam_height;
            float x1=detection_locations[4*i+1]*cam_width;
            float y2=detection_locations[4*i+2]*cam_height;
            float x2=detection_locations[4*i+3]*cam_width;

            Rect rec((int)x1, (int)y1, (int)(x2 - x1), (int)(y2 - y1));
            rectangle(src,rec, Scalar(0, 0, 255), 1, 8, 0);
            printf("label %d", Labels[det_index].c_str());
            putText(src, format("%s", Labels[det_index].c_str()), Point(x1, y1-5) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
            */
        }

    }

    if(!detect_state)
    {
        // no find pet
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
    mFeedCount = mFeed;
}
int Detect_pet_thread::getFeedCount()
{
    return mFeedCount;
}
