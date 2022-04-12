 #include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // start detection threads
    mWeight_detect_thread  = new Weight_detect_thread();
    // sliding bar for measuring feeding weights
    mWeight_detect_thread->setWeightValue = ui->horizontalSlider;

    // threads for pet detection
    mDetect_pet_thread = new Detect_pet_thread();
    initPin();
}

MainWindow::~MainWindow()
{
    delete ui;
}
// click on the test button to start the testing process which includes
// 1. Starting the weight sensor h711 detection thread
// 2. Starting the imaging pet detection threads
void MainWindow::on_start_detect_clicked()
{
    detect_w = true;
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setSingleStep(1);

    mDetect_pet_thread->start();
    mWeight_detect_thread->start();
}

// Turning on the camera preview
void MainWindow::on_open_camera_clicked()
{
    Time_camera = new QTimer(this);
    connect(Time_camera, SIGNAL(timeout()), this, SLOT(open_camera_time_click()));
    Time_camera->start(30);//30ms refreshing camera fps=30
    frame = cap.open(0);
    //frame = cap.open("1.mp4");
    if(!cap.isOpened()){
        printf("open camera failed !");
    }

}


// Camera refreshing
// Imaging refreshing
// Obtaining weight sensor values
// Seting the weight values
// Copying image data for pet detection
void MainWindow::open_camera_time_click(){
    // Executing the function every 30ms
    float h771OutValue =0;
    if (detect_w == true) {

        h771OutValue = mWeight_detect_thread->getH711Value();
        qDebug("run.... %f", h771OutValue);
    }


    // Display of set feeding weight
    QString weightshow;
    int setWight = ui->horizontalSlider->value();
    weightshow.sprintf("%d (g)", setWight);// int to string
    ui->label_set_weight_show->setText(weightshow);

    if(setWight > h771OutValue)
    {
        //open motion
        qDebug("water.........................");
        digitalWrite(water_motion_pin, 1);
        //delay(2000);
        //digitalWrite(water_motion_pin, 0);
        //delay(2000);

    }else {

    }


    // read image
    cap.read(frame);
    //resize(frame, frame, Size());
    if (mDetect_pet_thread != nullptr) {
        mDetect_pet_thread->setMainThreadImage(frame);
        int feedPetCount = mDetect_pet_thread->getFeedCount();
        QString feedCountshow;
        feedCountshow.sprintf("%d ", feedPetCount);
        ui->feed_count->setText(feedCountshow);
    }



    // Creating display containers
    //cvtColor(frame, frame, );
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage showImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    // Adding a file to the container with fileName(QString type)as its path
    scene->addPixmap(QPixmap::fromImage(showImage));
    // Display the contents of the container with the help of the graphicsView (QGraphicsView class) control
    ui->graphicsView_camera->setScene(scene);
    // Starting display
    ui->graphicsView_camera->show();
}

void MainWindow::initPin()
{
    wiringPiSetup();
    pinMode(water_motion_pin, OUTPUT);

}

// exit
void MainWindow::on_bt_stop_clicked()
{   printf("exit....");
    this->close();
}

