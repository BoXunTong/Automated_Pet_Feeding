#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "mattoqimage.h"

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

private slots:
    void start_clicked();
    void capturing();
    void stop_clicked();

private:
    Ui::MainWindow *ui;
    VideoCapture    capture;
    Mat             frame;
    QPixmap        *pixmap;
    QTimer         *intervalTimer;
    QGraphicsScene *scene;
    MatToQimage mMatToQimage;
};

#endif // MAINWINDOW_H
