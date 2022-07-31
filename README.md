# Auto-Feeding Pets Machine
For more details please check the [wiki](https://github.com/BoXunTong/Automated_Pet_Feeding/wiki).


# 1. Project Introduction

(1)Automatically detecting the approach of pets.

(2)The weight sensor detects in real time whether there is food in the bowl.

(3)Record the pet's health status, and send an alarm when the food intake is abnormal.



# 2. Configuration Requirements

## 2.1 Hardware
(1)Raspberry Pi(Raspberry Pi 4 Model B)

Raspberry Pi is a series of single-board computers ranging from $20-$60 CND. The version of Raspberry Pi we are looking at includes 1GB of RAM, ARM compatible CPU, GPU, MicroSDHC memory storage, 4 USB ports, Ethernet port, as well as WiFi and Bluetooth capabilities. The Raspberry Pi uses a Linux-Kernel based OS, Raspbian.
The Raspberry Pi will act as our central processing unit, controlling all other components of the tank itself. The Raspberry Pi does not have a real-time clock built in, and will need to be reset after each power off. Raspberry Pi runs on Python natively, however we would like to use C++ to take advantage of the Automatic Pet Feeding System.

(2)Youmile HX711 Weight Sensor

On-chip power supply regulator for load-cell and ADC analog power supply, On-chip active low noise PGA with selectable gain of 32,64 and 128, Simple digital control and serial interface: pin-driven controls, no programming needed, selectable 10SPS or 80SPS output data rate. Operation supply voltage range: 2.6 ~ 5.5V. Current consumption including on-chip analog power supply regulator: normal operation < 1.5mApower down < 1uA.

(3)DC Water pump  5V

(4)Relay

![电路图1](https://user-images.githubusercontent.com/99829195/164106135-2f8136bd-c377-4520-a72b-ac098054a747.jpg)

![电路图2](https://user-images.githubusercontent.com/99829195/164106155-6315b304-3217-4cd3-88f7-291663c1088a.jpg)

## 2.2 Software
(1)Qt/GUI

(2)Threads/Timing

The code is in Code folder.

The code structure diagram of the software is as follows.


![Main thread MainWindow](https://user-images.githubusercontent.com/98624810/182033148-d29f601d-14c4-484d-8a09-5fbab50d336c.jpg)





# 3. Getting Started

## 3.1 Prerequisites

HX711 and Qt5 are required. Users can use following script to install:

*git clone --depth= 1 https://github.com/endail/hx711*

*cd hx711*

*make && sudo make install*

## 3.2 Build Application Manually

1. Get the “HX711_demo” package. And put it under the “projects” folder.

2. Install Dependency with Script (HX711)

   *git clone --depth= 1 https://github.com/endail/hx711*
   
   *cd hx711*
   
   *make && sudo make install*

3. Find the “HX711_demo.pro” document and build it.
![image](https://user-images.githubusercontent.com/98624810/182037413-6a5a140d-15a7-48c6-99e8-4b86c570b943.png)


4. Find the “build-hx711_demo-Desktop-Debug” folder
![image](https://user-images.githubusercontent.com/98624810/182037420-67d3fb8f-054c-43b0-a213-2009364df7c5.png)


5. Run the application

   *cd projects/build-hx711_demo-Desktop-Debug*
   
   *./HX711_demo*



# 4. Roadmap

View Project Plan Gantt

![Project_Plan_Gantt](https://user-images.githubusercontent.com/98624810/182037332-55271515-0b66-4416-b272-bda6f576a39d.png)

View issue list

https://github.com/BoXunTong/Automated_Pet_Feeding/issues



# 5. Social Media

**YouTube**(Include project introduction video)

https://youtu.be/xPs7qO0fQtA

**Twitter**

https://twitter.com/XueyanZhang2637

**Instagram**

https://www.instagram.com/autofeedingpetsmachine_/



# 6. Contact

This project is being completed by four students majoring in Computer Systems Engineering at the University of Glasgow.

- [Boxun Tong](https://github.com/BoXunTong)

- [Yue Yu](https://github.com/Yue2022pro)

- [Yucheng Zhi](https://github.com/zyc2333333)

- [Xueyan Zhang](https://github.com/Vrachaos)
