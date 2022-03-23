#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<opencv2/opencv.hpp>

using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    printf("init...");
    ui->setupUi(this);
    intervalTimer = new QTimer(this);
    pixmap = new QPixmap();
    scene = new QGraphicsScene();
    connect(ui->openCamera, SIGNAL(clicked()), this, SLOT(start_clicked()));
    connect(ui->closeCamera, SIGNAL(clicked()), this, SLOT(stop_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pixmap;
    delete scene;
    delete intervalTimer;
}

void MainWindow::start_clicked() {
    printf("connect on_staet_slot \n");
    bool ret = capture.open("traffic_light.mp4");
    if(!ret) {
        printf("open video or camera failed!\n");
        return;
    }
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    printf("connect intervalTimer \n");
    intervalTimer->start(33);
}

void MainWindow::capturing() {
    printf("connect capturing... \n");
    capture.read(frame);
    QImage result = mMatToQimage.QImageFromMat(frame);
    pixmap = new QPixmap(QPixmap::fromImage(result));
    scene = new QGraphicsScene(ui->graphicsView);
    scene->addPixmap(*pixmap);
    scene->setSceneRect(pixmap->rect());
    ui->graphicsView->setScene(scene);
}

void MainWindow::stop_clicked() {
    intervalTimer->stop();
    disconnect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    capture.release();
}
