#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //start detection threads
    mWeight_detect_thread  = new Weight_detect_thread();
    mWeight_detect_thread->setWeightValue = ui->horizontalSlider;
    //feeding weight sliders
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(2000);
    ui->horizontalSlider->setSingleStep(20);


    //threads detection
    mDetect_pet_thread = new Detect_pet_thread();
    initPin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Click on the detection button to start detection including
//1. opening the quality sensor h711 detection thread
//2. opening the image pet detection thread
void MainWindow::on_start_detect_clicked()
{
    detect_w = true;


    mDetect_pet_thread->start();
    mWeight_detect_thread->start();
}

//Open camera preview
void MainWindow::on_open_camera_clicked()
{
    Time_camera = new QTimer(this);
    connect(Time_camera, SIGNAL(timeout()), this, SLOT(open_camera_time_click()));
    Time_camera->start(30);//30ms refresh camera fps=30
    frame = cap.open(0);
    //frame = cap.open("cat.flv");
    if(!cap.isOpened()){
        printf("open camera failed !");
    }

}


//In camera refresh, the following was done
//refreshing the image
//Get mass sensor values
//set the feeding quality
//copy image data for pet detection
void MainWindow::open_camera_time_click(){
    mTime_curr++;
    // Execute the function every 30ms
    int h771OutValue =0;
    if (detect_w == true) {

        h771OutValue = mWeight_detect_thread->getH711Value();
        if(h771OutValue < 0) {
            h771OutValue  = 0;
        }
        //qDebug("run.... %f", h771OutValue);
    }


    // Display of set feeding weight
    QString weightshow;
    int setWight = ui->horizontalSlider->value();
    weightshow.sprintf("%d (g)", setWight);// float to string
    ui->label_set_weight_show->setText(weightshow);
	qDebug("set food ");
    QString leftover;
    leftover.sprintf("%d (g)", h771OutValue);// int to string
    ui->last_value->setText(leftover);

    //Fetching
    cap.read(frame);
    cv::resize(frame, frame, Size(560,390));
    bool pet_state = false;
    if (mDetect_pet_thread != nullptr) {
        mDetect_pet_thread->setMainThreadImage(frame);
        int feedPetCount = mDetect_pet_thread->getFeedCount();
        QString feedCountshow;
        feedCountshow.sprintf("%d ", feedPetCount);
        ui->feed_count->setText(feedCountshow);

        if (mDetect_pet_thread->getFindCat()){
            putText(frame, "FIND a DOG", Point(10, 20) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
            pet_state = true;
            mTime_curr = 0;
            digitalWrite(water_motion_pin, 1);
        }else {
            digitalWrite(water_motion_pin, 0);
            pet_state = false;
            putText(frame, "DETECT RUNING", Point(10, 20) ,FONT_HERSHEY_SIMPLEX,0.5, Scalar(0, 0, 255), 1, 8, 0);
        }
    }

    if(setWight > h771OutValue && pet_state)
    {
        //open motion
        qDebug("water motor runing...");
        digitalWrite(water_motion_pin, 1);
        //delay(2000);


    }else {
        digitalWrite(water_motion_pin, 0);
        //delay(2000);
    }
    if(mTime_curr > 30*60*60*24){
        ui->healthy->setText("abnormal");
    } else {
        ui->healthy->setText("healthy");
    }


    // Create display containers
    //cvtColor(frame, frame, );
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage showImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    // Add a file to the container with fileName (QString type) as its path
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(showImage));
    // Display the contents of the container with the help of the graphicsView (QGraphicsView class) control
    ui->graphicsView_camera->setScene(scene);
    // Start display
    ui->graphicsView_camera->show();
}

void MainWindow::initPin()
{

    pinMode(water_motion_pin, OUTPUT);
    /*digitalWrite(water_motion_pin, HIGH);
    delay(2000);
    digitalWrite(water_motion_pin, LOW);
    delay(2000);
    qDebug("init...-----");*/
}

//Exit
void MainWindow::on_bt_stop_clicked()
{   printf("exit....");
    this->close();
}

