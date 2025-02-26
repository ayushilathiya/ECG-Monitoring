# ECG Monitoring System

This repository contains the code and schematics for a portable ECG (Electrocardiogram) monitoring system. The device is designed to continuously monitor heart activity and transmit data for remote analysis, providing real-time cardiac health insights.

## Features

- **Continuous Monitoring**: Records ECG signals 24/7, suitable for long-term heart activity tracking.
- **Portability**: Compact design allows patients to carry the device comfortably, facilitating daily monitoring without hindrance.
- **Remote Data Transmission**: Utilizes IoT technology to send ECG data to healthcare providers in real-time, enabling prompt medical interventions.
- **Low Power Consumption**: Incorporates solar charging and rechargeable batteries to ensure extended usage without frequent recharging.

## Hardware Components

- **ECG Sensor Module**: Captures the electrical activity of the heart.
- **Microcontroller (e.g., ESP32)**: Processes sensor data and manages communication protocols.
- **GPS Module**: Tracks the patient's location for emergency response.
- **Power Supply**: Solar panels and rechargeable batteries for sustainable power management.

## Software Overview

The software is developed using C++ and is compatible with the Arduino IDE. It handles data acquisition from sensors, processes the ECG signals, and transmits the information to a remote server or mobile application via Wi-Fi or Bluetooth.

### Key Functionalities

- **Data Acquisition**: Reads real-time data from ECG and other health sensors.
- **Signal Processing**: Filters and processes raw ECG signals to remove noise and artifacts.
- **Data Transmission**: Sends processed data to a remote server or mobile app for monitoring and analysis.
- **Alert System**: Generates alerts if abnormal heart activities are detected, facilitating immediate medical attention.

## Getting Started

### Prerequisites

- **Hardware Setup**: Assemble the components as per the provided schematic diagram (`schematic.png` in the repository).
- **Software Tools**: Install the Arduino IDE and necessary libraries for the sensors and microcontroller used.

### Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ayushilathiya/ECG-Monitoring.git
