#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //开启检测线程
    mWeight_detect_thread  = new Weight_detect_thread();
    mWeight_detect_thread->setWeightValue = ui->horizontalSlider;
    //投喂重量滑动条
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(2000);
    ui->horizontalSlider->setSingleStep(20);


    //检测线程
    mDetect_pet_thread = new Detect_pet_thread();
    initPin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//点击检测按钮，开始检测包括
//1. 开启质量传感器h711检测线程
//2. 开启图像宠物检测线程
void MainWindow::on_start_detect_clicked()
{
    detect_w = true;


    mDetect_pet_thread->start();
    mWeight_detect_thread->start();
}

//打开摄像头预览
void MainWindow::on_open_camera_clicked()
{
    Time_camera = new QTimer(this);
    connect(Time_camera, SIGNAL(timeout()), this, SLOT(open_camera_time_click()));
    Time_camera->start(30);//30ms刷新一次camera fps=30
    frame = cap.open(0);
    //frame = cap.open("cat.flv");
    if(!cap.isOpened()){
        printf("open camera failed !");
    }

}


//摄像头刷新中，做了以下工作
//刷新图像
//获取质量传感器数值
//设置投喂质量
//拷贝图像数据，用于检测宠物
void MainWindow::open_camera_time_click(){
    mTime_curr++;
    //每30ms执行一次函数
    int h771OutValue =0;
    if (detect_w == true) {

        h771OutValue = mWeight_detect_thread->getH711Value();
        if(h771OutValue < 0) {
            h771OutValue  = 0;
        }
        //qDebug("run.... %f", h771OutValue);
    }


    //显示设置投喂重量
    QString weightshow;
    int setWight = ui->horizontalSlider->value();
    weightshow.sprintf("%d (g)", setWight);// float to string
    ui->label_set_weight_show->setText(weightshow);
	qDebug("set food ");
    QString leftover;
    leftover.sprintf("%d (g)", h771OutValue);// int to string
    ui->last_value->setText(leftover);

    //取图
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


    //创建显示容器
    //cvtColor(frame, frame, );
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage showImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    //向容器中添加文件路径为fileName（QString类型）的文件
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(showImage));
    //借助graphicsView（QGraphicsView类）控件显示容器的内容
    ui->graphicsView_camera->setScene(scene);
    //开始显示
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

//退出
void MainWindow::on_bt_stop_clicked()
{   printf("exit....");
    this->close();
}

