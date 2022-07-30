#include "hx711_thread.h"

//2, 3, 1269, -385160
/*hx711_thread::hx711_thread(int pin_dt, int pin_sck, int refer, int offset){
    hx = new SimpleHX711(2, 3, 1269, -385160);
    hx.setUnit(Mass::Unit::OZ);
    //qDebug("setup ....");
}*/

hx711_thread::hx711_thread():hx(2, 3, 1269, -385160){
    hx.setUnit(HX711::Mass::Unit::OZ);
    //qDebug("setup ....");
}

hx711_thread::~hx711_thread(){
    //强制关闭窗口时，线程也能安全关闭
     requestInterruption();
     wait();
}
void hx711_thread::setWeightState(bool mWeightState)
{
    m_WeightState = mWeightState;
}

bool hx711_thread::getWeightState()
{
    return m_WeightState;
}

void hx711_thread:: setHx711ValueFromUi(int mValue)
{
    water_weight_ui_threshold = mValue;
}

int hx711_thread:: getHx711Value()
{
    return m_weight_value;
}

void hx711_thread::run()
{
    //std::cout<<"run"<<std::endl;
    while(!isInterruptionRequested())
    {
        //std::cout<<"run"<<std::endl;
        time_count++;
        starts=clock();
        m_weight_value = (int)hx.weight(10);
        ends=clock();
        if(time_count % 10 == 0) {
            std::cout<<"detect_weight cost time = " << (ends - starts) / 10000<< " ms" <<std::endl;
            //std::cout<<"detect_weight cost time = " << m_weight_value << " g" <<std::endl;
            time_count = 0;
        }

        std::cout<<"water_weight_ui_threshold = " << water_weight_ui_threshold << " g" <<std::endl;
        if(m_weight_value < water_weight_ui_threshold){
            //setWeightState(true);
            m_globalwrapper_MM = 1;
            //std::cout<<"water_weight_ui_threshold = " << water_weight_ui_threshold << " g" <<std::endl;
            //m_globalwrapper.tests_run(1);
            //int getN = m_globalwrapper.tests_run();
            //std::cout<<"getN = " << getN << " g" <<std::endl;
        } else {
            m_globalwrapper_MM = 0;
            //setWeightState(false);
            //m_globalwrapper.tests_run(0);
        }

        msleep(10);

    }
}
