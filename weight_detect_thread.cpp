#include "weight_detect_thread.h"

#include<QThread>
#include <QSlider>
# include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
//# include <wiringPi.h>

Weight_detect_thread::Weight_detect_thread()
{
    //初始化进度条控件
    setWeightValue = new QSlider;
    //初始化传感器

    int init = setup(&hx711);
    if (init == 1){
        qDebug("setup failed....");
    }
    qDebug("setup ....");
}

Weight_detect_thread::~Weight_detect_thread()
{
    //强制关闭窗口时，线程也能安全关闭
     requestInterruption();
     wait();
}

void Weight_detect_thread::run()
{
    while(!isInterruptionRequested())
    {
        /* test
        std::ifstream inFile;
        inFile.open("data.txt");
        inFile>>h711Value;
        inFile.close();*/
        qDebug("detect_weight run....");
        start_detect_weight(&hx711);

        msleep(1000);

    }
}

void Weight_detect_thread::setH711Value(int mValue)
{
    h711Value = mValue;
}

int Weight_detect_thread::getH711Value()
{
    return h711Value;
}


void Weight_detect_thread::set_pin(struct hx711_pin *value){
    value->SCK             = 2;
    value->SDA             = 3;
    value->EN              = 1;
    value->coefficient    = 415;
}

void Weight_detect_thread::init_pin(struct hx711_pin *value){
    /*
    pinMode(value->SCK,OUTPUT);
    pinMode(value->SDA,INPUT);
    pullUpDnControl(value->SDA,PUD_UP);
    */


    //pinMode(29, OUTPUT);
    //pullUpDnControl(29, PUD_UP);
}

void Weight_detect_thread::start_detect_weight(struct hx711_pin *value){
    /*
    int i;

    digitalWrite(value->SCK, LOW);        //使能AD
    while(digitalRead(value->SCK));
    value->value = 0;                    //数值
    while(digitalRead(value->SDA));        //AD转换未结束则等待。
    delay(100);
    for(i=0;i<24;i++){
        digitalWrite(value->SCK,HIGH);
        while(0 == digitalRead(value->SCK))delay(1000);
        value->value = value->value*2;
        digitalWrite(value->SCK, LOW);
        while(digitalRead(value->SCK));
        if(digitalRead(value->SDA))
            value->value = value->value + 1;
    }
    digitalWrite(value->SCK, HIGH);
    digitalWrite(value->SCK, LOW);
    if((value->EN == 1)&&(value->value<25000)){
        value->EN = 0;
        value->calibration = value->value;
    }else {
        i = (value->value-value->calibration+50)/value->coefficient;
    }
    if(i<1000){
        value->weight = i;
    }

    h711Value = value->weight;
    */
}

/*-----------------主体-----------------*/
int Weight_detect_thread::setup(struct hx711_pin *value){
    /*
    if(wiringPiSetup()==-1)return 1;
    set_pin(value);
    init_pin(value);
    */
    return 0;

}
