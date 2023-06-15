# BLE Sensor-Drone AgrIoT Project 🌱🤖

## Introduction
This project implements the communication required for the AgrIot project using Bluetooth Low Energy(BLE) and the [ESP32] (https://www.espressif.com/en/products/socs/esp32) microcontroller. The project is divided into two parts: the BLE sensor and the BLE drone. The BLE sensor is responsible for collecting data from the sensors and sending it to the BLE drone. The BLE drone is responsible for receiving the data from the BLE sensor and sending it to the cloud.

## BLE Sensor
The BLE sensor is responsible for collecting data from the sensors and sending it to the BLE drone. The BLE sensor is implemented using the ESP32 microcontroller and the [Arduino IDE](https://www.arduino.cc/en/software).
The Sensor sends different sensor data using seperate characteristics in the BLE service. This acts as the server in the BLE connection

## BLE Drone
The BLE drone is responsible for receiving the data from the BLE sensor and storing it in memory. The BLE drone is implemented using the ESP32 microcontroller and the [Arduino IDE](https://www.arduino.cc/en/software). It acts as the client in the BLE connection. It listens for the data from the BLE sensor and stores it in memory.
