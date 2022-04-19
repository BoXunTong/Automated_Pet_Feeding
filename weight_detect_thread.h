#ifndef WEIGHT_DETECT_THREAD_H
#define WEIGHT_DETECT_THREAD_H

#include<QThread>
#include <QSlider>
# include <stdio.h>
# include <wiringPi.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>

class Weight_detect_thread: public QThread
{
    Q_OBJECT
public:
    Weight_detect_thread();
    QSlider *setWeightValue;
    int h711Value = 0;
    int getH711Value();
    float n1 = 0.0;
private:
    void setH711Value(int mValue);


    void run();

private:
    /*-----------------struct-----------------*/
     struct hx711_pin{
         int SCK;  //13 y
         int SDA;  //15 gray
         int EN;                        // Calibration enable
         int calibration;            // Calibration
         int coefficient;            // Scale factor
         int weight;                    // Weight
        unsigned long value;        // Record value
     }hx711;
     //hx711_pin ;
     void set_pin(struct hx711_pin *value);
     void init_pin(struct hx711_pin *value);
     void start_detect_weight(struct hx711_pin *value);
     int setup(struct hx711_pin *value);

};


#endif // WEIGHT_DETECT_THREAD_H
