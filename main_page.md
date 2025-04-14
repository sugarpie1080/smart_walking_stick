# Overview

This is the documentation for the ENG5220 Project: Smart Walking Stick.

**Objective**: Develop a smart walking stick equipped with obstacle detection and GPS navigation to assist visually impaired users in navigating their environment safely and independently.

---

# Problem Analysis

## Problem
Visually impaired individuals face significant challenges navigating both familiar and unfamiliar environments. Traditional aids like white canes are limited in their ability to detect obstacles beyond a short range and do not offer any directional or location-based guidance. This can result in a loss of independence, safety risks, and difficulty accessing everyday locations with confidence.

## Solution
The proposed smart walking stick integrates obstacle detection sensors and GPS navigation to provide real-time environmental awareness and directional assistance. The device alerts users to nearby obstacles and helps guide them to their destinations safely and independently. By combining essential mobility support with modern technology, it greatly enhances usability and functionality over conventional tools.

## Target Audience
The primary audience includes visually impaired individuals seeking greater independence in daily mobility. Secondary audiences may include organizations supporting individuals with disabilities, healthcare providers, and rehabilitation centers looking for assistive technologies that enhance patient outcomes.

## Critical Analysis
While there are some existing solutions in the assistive tech space, many are either prohibitively expensive, lack comprehensive navigation features, or are not user-friendly. This smart walking stick addresses those gaps by offering an affordable, intuitive, and integrated solution. However, success will depend on factors like battery life, durability, user training, and the reliability of sensors and GPS in various environments. Ensuring seamless functionality across different terrains and minimizing false positives in obstacle detection will be critical to user trust and adoption.

---
# Development Status

## Current Progress

- **Obstacle Detection**  
  - Implemented using the VL53L0X Time-of-Flight sensor  
  - Codebase: `src/application/ToFSensor.cpp`

- **Haptic Feedback System**  
  - Enabled through a haptic motor driver  
  - Feedback intensity is dynamically adjustable using an exponential response curve  
  - Codebase: `src/application/MotorMove.cpp`

- **Status Monitoring**  
  - Real-time data is transmitted to a Python-based web app via DDS (FastDDS)  
  - Currently hosted on a Raspberry Pi, with flexibility to run independently  
  - Codebase: `src/ToF_GUI/WebpageSubGUI.py`

---

## In Progress / To-Do

- Implement **Drop-Mode** functionality using the IMU sensor  
- Add **Battery Status Monitoring** for real-time power insights  
- Enable **Two-Way Communication** between the WebApp and the smart walking stick  
---

# Usage

## Hardware
The following hardware is required for this repository:
- Raspberry Pi 5
- VL53L0X ToF Sensor
- Vibrating Mini Motor Disc / Haptic Feedback Sensor
- Uninterruptible Power Supply UPS HAT
### Connections
<!-- Add Connections here -->

## Software
### Setup
The following setup is required:

1. Install libgpiod to access the pins:
```bash
    sudo apt install libgpiod
    sudo apt install colcon
    sudo apt install swig
    sudo apt install vcstool
```
2. Setup the PWM pin:
    - Add to `/boot/firmware/config.txt`
    ```bash 
        dtoverlay=pwm-2chan```
    Reboot the raspberry pi
    - Check that the overlay worked:
    ```bash 
    pinctrl -p```
3. Install `fastdds_python`, through following these instructions. [fastdds_python link](https://github.com/eProsima/Fast-DDS-python)
4. Source the `fastdds_python` install before compliation:
    ```bash
        source <path_to_fastdds_python_ws>/install/setup.bash
    ```

### Compliation



