#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "hx711_thread.h"
#include <opencv2/opencv.hpp>
#include <QGraphicsScene>
#include "camera_precess.h"
#include "detect_pet_thread.h"

using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    hx711_thread *mhx711_thread;
    Detect_pet_thread *mDetect_pet_thread;
private slots:
    void on_open_camera_clicked();
    void open_camera_preview_time();
    void on_bt_stop_clicked();
    void on_start_detect_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *Time_camera ;//camera的更新时间
    QGraphicsScene *scene = new QGraphicsScene;
    void initUi();
    void updateUi(Mat mFrame, int mH771OutValue);
    Camera_precess m_Camera_precess;
};

#endif // MAINWINDOW_H
