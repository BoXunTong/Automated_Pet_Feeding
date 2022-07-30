#include "motor_control.h"

Motor_control::Motor_control()
{

}

void Motor_control::motor_run()
{
    //digitalWrite(water_motion_pin, 1);
    cout<<"callback motor_run ..." <<endl;
}

void Motor_control::motor_stop()
{
    //digitalWrite(water_motion_pin, 0);
    cout<<"callback motor_stop ..." <<endl;
}

void Motor_control::find_pets() {
    cout<<"callback motor ..." <<endl;
    motor_run();
    printf("I'am ProgramA.FunA2() and be called..\n");
}
void Motor_control::initPin()
{
    printf("Motor_control::initPin()..\n");

    //pinMode(water_motion_pin, OUTPUT);
    /*digitalWrite(water_motion_pin, HIGH);
    delay(2000);
    digitalWrite(water_motion_pin, LOW);
    delay(2000);
    qDebug("init...-----");*/
}
