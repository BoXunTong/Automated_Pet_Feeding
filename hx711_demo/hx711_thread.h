#ifndef HX711_THREAD_H
#define HX711_THREAD_H

#include <hx711/common.h>
#include <iostream>
#include <QThread>
#include "globalwrapper.h"


class hx711_thread: public QThread
{
    Q_OBJECT
public:
    hx711_thread();
    ~hx711_thread();
    int getHx711Value();
    void setWeightState(bool mWeightState);
    bool getWeightState();
    void setHx711ValueFromUi(int mValue);
private:

    void run();
private:
    int m_weight_value = 0;
    bool m_WeightState = false;
    clock_t starts, ends;
    int time_count = 0;
    HX711::SimpleHX711 hx;
    int water_weight_ui_threshold = 0;
    globalWrapper m_globalwrapper;
};

#endif // HX711_THREAD_H
