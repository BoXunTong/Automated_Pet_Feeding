#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <weight_detect_thread.h>
#include <opencv2/opencv.hpp>
#include "detect_pet_thread.h"
#include <wiringPi.h>

//using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Variable declaration
    QString setWeightValueshow;
    Weight_detect_thread *mWeight_detect_thread;

    QTimer *Time_camera ;// Camera update time

    //camera
    cv::VideoCapture cap;
    cv::Mat frame;
    QGraphicsScene *scene = new QGraphicsScene;

    // Switches dectection
    bool detect_w = false;

    // Threads dectection
    Detect_pet_thread *mDetect_pet_thread;
    void initPin();
    int water_motion_pin = 29;
    int mm = 0;
    int mTime_curr = 0;

private slots:
    // Inline
    void on_start_detect_clicked();
    void on_open_camera_clicked();
    void on_bt_stop_clicked();

    void open_camera_time_click();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
