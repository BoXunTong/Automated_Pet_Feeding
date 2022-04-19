#include "weight_detect_thread.h"

Weight_detect_thread::Weight_detect_thread()
{
    // Initialize progress bar control
    setWeightValue = new QSlider;
    // Initialize sensor

    int init = setup(&hx711);
    if (init == 1){
        qDebug("setup failed....");
    }
    qDebug("setup ....");
}

void Weight_detect_thread::run()
{
    while(true)
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
    pinMode(value->SCK,OUTPUT);
    pinMode(value->SDA,INPUT);
    pullUpDnControl(value->SDA,PUD_UP);


    //pinMode(29, OUTPUT);
    //pullUpDnControl(29, PUD_UP);
}

void Weight_detect_thread::start_detect_weight(struct hx711_pin *value){
    int i;

    digitalWrite(value->SCK, LOW);        // Enable AD
    while(digitalRead(value->SCK));
    value->value = 0;                    // Value
    while(digitalRead(value->SDA));        // Wait if AD conversion is not over
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
}

/*-----------------main-----------------*/
int Weight_detect_thread::setup(struct hx711_pin *value){
    if(wiringPiSetup()==-1)return 1;
    set_pin(value);
    init_pin(value);
    return 0;
}
