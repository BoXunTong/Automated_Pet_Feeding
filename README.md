# Auto-Feeding Pets Machine
# Introduction
(1)Automatically detecting the approach of pets.

(2)The weight sensor detects in real time whether there is food in the bowl.

(3)Record the pet's health status, and send an alarm when the food intake is abnormal.



# Configuration Requirements

# 1、Hardware
(1)Raspberry Pi(Raspberry Pi 4 Model B)

Raspberry Pi is a series of single-board computers ranging from $20-$60 CND. The version of Raspberry Pi we are looking at includes 1GB of RAM, ARM compatible CPU, GPU, MicroSDHC memory storage, 4 USB ports, Ethernet port, as well as WiFi and Bluetooth capabilities. The Raspberry Pi uses a Linux-Kernel based OS, Raspbian.
The Raspberry Pi will act as our central processing unit, controlling all other components of the tank itself. The Raspberry Pi does not have a real-time clock built in, and will need to be reset after each power off. Raspberry Pi runs on Python natively, however we would like to use C++ to take advantage of the Automatic Pet Feeding System.

(2)Youmile HX711 Weight Sensor

On-chip power supply regulator for load-cell and ADC analog power supply, On-chip active low noise PGA with selectable gain of 32,64 and 128, Simple digital control and serial interface: pin-driven controls, no programming needed, selectable 10SPS or 80SPS output data rate. Operation supply voltage range: 2.6 ~ 5.5V. Current consumption including on-chip analog power supply regulator: normal operation < 1.5mApower down < 1uA.

(3)DC Water pump  5V

(4)Relay

![电路图1](https://user-images.githubusercontent.com/99829195/164106135-2f8136bd-c377-4520-a72b-ac098054a747.jpg)

![电路图2](https://user-images.githubusercontent.com/99829195/164106155-6315b304-3217-4cd3-88f7-291663c1088a.jpg)

# 2、Software
(1)Qt/GUI

(2)Threads/Timing

The code is in test_qt folder.

![微信图片_20220419234246](https://user-images.githubusercontent.com/99829195/164113626-5c8937d7-7869-4a2b-8e7b-714f028e11ea.png)







# YouTube Link

https://youtu.be/wU3hO5N8FNw





