#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
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
    mCamera_precess.openCamera();
}

void MainWindow::open_camera_preview_time()
{
    Mat frame = mCamera_precess.previewCamera();
    QImage showImage = QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(showImage));
    ui->graphicsView_camera->setScene(scene);
    ui->graphicsView_camera->show();
}

void MainWindow::on_bt_stop_clicked()
{
    printf("exit....");
    this->close();
}
