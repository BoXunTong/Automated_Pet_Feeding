#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    initUi();
    //检测线程
    mDetect_pet_thread = new Detect_pet_thread();
    mWeight_detect_thread  = new Weight_detect_thread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_camera_clicked()
{
    Time_camera = new QTimer(this);
    connect(Time_camera, SIGNAL(timeout()), this, SLOT(open_camera_preview_time()));
    Time_camera->start(30);//30ms刷新一次camera fps=30


}

void MainWindow::open_camera_preview_time()
{
    //Mat frame = mCamera_precess.previewCamera();
    //mDetect_pet_thread->setMainThreadImage(frame);
    int h771OutValue = mWeight_detect_thread->getH711Value();
    //updateUi(frame, h771OutValue);
}

void MainWindow::on_bt_stop_clicked()
{
    printf("exit....");
    this->close();
}

void MainWindow::on_start_detect_clicked()
{
    mDetect_pet_thread->start();
    //mWeight_detect_thread->start();
}

void MainWindow::initUi()
{
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(2000);
    ui->horizontalSlider->setSingleStep(20);

}

void MainWindow::updateUi(Mat mFrame, int mH771OutValue)
{
    QImage showImage = QImage(mFrame.data, mFrame.cols, mFrame.rows, QImage::Format_RGB888);
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(showImage));
    ui->graphicsView_camera->setScene(scene);
    ui->graphicsView_camera->show();

    //显示设置投喂重量
    QString weightshow;
    int setWight = ui->horizontalSlider->value();
    weightshow.sprintf("%d (g)", setWight);// float to string
    ui->label_set_weight_show->setText(weightshow);
    QString leftover;
    leftover.sprintf("%d (g)", mH771OutValue);// int to string
    ui->last_value->setText(leftover);
}
