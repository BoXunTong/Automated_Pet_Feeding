#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include<iostream>
//#include <wiringPi.h>

using namespace std;

class Motor_control
{
public:

    Motor_control();
    static void motor_run();
    static void motor_stop();
    bool motor_usable(bool usable_motor);
    //fun
    static void find_pets();
    static void initPin();
private:

    static const int water_motion_pin = 7;
};

#endif // MOTOR_CONTROL_H
