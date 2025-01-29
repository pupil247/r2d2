# Robot Project - ESP32 Control System  

## Overview  
This project is the control system for a R2D2 robot I made, powered by an ESP32. The ESP32 is responsible for managing peripherals, executing pathfinding algorithms, and processing data from sensors. It works alongside a main processing unit to enable functionalities such as facial recognition, object detection, and autonomous navigation.

## Features  
- **Peripheral Control:** Manages motors, servos, and sensors.  
- **Facial Recognition:** Supports facial detection and recognition (processed externally).  
- **Object Detection:** Uses a camera module to detect and classify objects.  
- **Pathfinding:** Implements algorithms to navigate the environment efficiently.  
- **Communication:** Uses Wi-Fi for data exchange with the main processor.  

## Hardware Requirements  
- **ESP32** (e.g., ESP32-WROOM, ESP32-S3)  
- **Camera Module** (OV2640 for ESP32-CAM)  
- **LiDAR or Ultrasonic Sensors** for obstacle detection  
- **Motor Drivers** to control movement  
- **Battery Pack** and power management circuit  

## Software Stack  
- **ESP-IDF / Arduino Framework** – For ESP32 firmware development  
- **NimBLE Bluetooth Stack** – For efficient BLE communication  
- **cJSON Library** – For handling JSON data exchanges  
- **Motor Control Libraries** – For PWM-based motor driving  

## Installation  

### Prerequisites  
- Install **ESP-IDF** or **Arduino IDE** for ESP32 development.  
- Install dependencies using ESP-IDF:  
  ```bash
  idf.py install
