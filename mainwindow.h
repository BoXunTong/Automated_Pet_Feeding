#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "camera_precess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_open_camera_clicked();
    void open_camera_preview_time();
    void on_bt_stop_clicked();
    //void on_start_detect_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *Time_camera ;//camera的更新时间
    Camera_precess mCamera_precess;
    QGraphicsScene *scene = new QGraphicsScene;


};
#endif // MAINWINDOW_H
