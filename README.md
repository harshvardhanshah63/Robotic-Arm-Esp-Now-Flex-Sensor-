# 🤖 Robotic Arm : EXOGENESIS

A wireless robotic hand system controlled using flex sensors and ESP32 microcontrollers.  
The system captures human finger movements through a glove and replicates them on a robotic hand using servo motors and ESP-NOW communication.

---

## 📌 Introduction

Robotic systems are widely used in medical, industrial, and educational fields.  
This project focuses on building a wireless robotic hand that mimics human finger movements using flex sensors and ESP32 boards.

Finger movements are detected using a wearable glove and transmitted wirelessly to a robotic hand, where servo motors reproduce the same motion.
<img width="913" height="302" alt="image" src="https://github.com/user-attachments/assets/d5e2b89a-f1d4-495e-9b03-c64767c644f4" />

---

## 🎥 Project Demonstration & Prototype Testing

### YouTube Testing Videos
1. https://youtube.com/shorts/7Oa2iwueIwg?si=Fzh45fDLNvpiwW9M  
2. https://youtube.com/shorts/HdQvleQe6Do?si=t_su_lGh6K9XxUNW  

These videos show real-time testing and prototype performance of the robotic hand system.

---

### 🔗 LinkedIn Project Posts
1. https://www.linkedin.com/posts/harshvardhanshah63_robotics-embeddedsystems-hardwareprojects-activity-7410461919540752384-7Hrv  
2. https://www.linkedin.com/posts/harshvardhanshah63_roboticsdemo-mechatronics-esp32-activity-7410465693500022785-tMFq  

These posts document the project development, prototype demonstration, and technical insights.

---

## 🎯 Objectives

- Design a wearable glove using flex sensors  
- Transmit data wirelessly using ESP-NOW  
- Control servo motors for realistic movement  
- Build a low-cost and efficient system  
- Ensure real-time performance  

---

## ⚙️ System Overview

The system consists of two main units:

### 1️⃣ Sender Unit (Glove Side)
- ESP32  
- Flex Sensors  
- Voltage Divider Circuit  
- Power Supply  

Reads finger movements and sends data wirelessly.

### 2️⃣ Receiver Unit (Robotic Hand Side)
- ESP32  
- Servo Motors  
- Robotic Hand Structure  
- Power Supply  

Receives data and controls servos.
<img width="913" height="295" alt="image" src="https://github.com/user-attachments/assets/6d561544-cdfa-48fc-8248-7b8ecdc53e5a" />

---

## 🧩 Hardware Components

### ESP32 Microcontroller
- Dual-core processor  
- Built-in WiFi & Bluetooth  
- Supports ESP-NOW  

### Flex Sensors
- Resistance changes when bent  
- Used for finger detection  

### Servo Motors
- Angle range: 0°–180°  
- Controlled using PWM  

---

## 💻 Software Requirements

- Arduino IDE  
- ESP32 Board Package  
- ESP32Servo Library  
- ESP-NOW Library  

---

## 🔁 Working Principle

1. Flex sensors change resistance when bent  
2. ESP32 reads analog values  
3. Resistance is calculated  
4. Noise is reduced using smoothing  
5. Finger states are detected using hysteresis  
6. Data is sent via ESP-NOW  
7. Receiver gets data  
8. Servos rotate accordingly  
9. Robotic hand mimics movement  

---

## 🧠 Algorithms Used

### Smoothing Algorithm
Moving average filter reduces noise.

### Hysteresis Algorithm
Prevents frequent switching using two thresholds.

### Servo Control Algorithm
Maps finger states to servo angles.

---

## 🛠️ Code Implementation

### Sender Unit (Glove)
Main Functions:
- Read flex sensors  
- Apply filtering  
- Calculate resistance  
- Send data wirelessly  

### Receiver Unit (Hand)
Main Functions:
- Receive ESP-NOW data  
- Control servo motors  
- Implement safety timeout  

> Refer to source code files for full implementation.

---

## ⚡ Hardware Connections

### Flex Sensors (Sender)
- One end → 3.3V  
- Other end → ADC Pin  
- 200kΩ resistor → GND  

### Servo Motors (Receiver)
- Red → 5V External Supply  
- Brown/Black → GND  
- Yellow/White → PWM Pin  

> Use common ground between ESP32 and power supply.

---

## FLOW CHART
<img width="940" height="885" alt="image" src="https://github.com/user-attachments/assets/a2703954-d84e-4317-8d85-3b715200539e" />

---
## 🚀 Setup Procedure

1. Install Arduino IDE  
2. Install ESP32 board package  
3. Install required libraries  
4. Upload receiver code  
5. Note receiver MAC address  
6. Update sender MAC address  
7. Upload sender code  
8. Connect hardware  
9. Test finger movement  
<img width="994" height="400" alt="image" src="https://github.com/user-attachments/assets/f90cf50f-e603-4e85-b365-1691deaf5778" />

---

## 📊 Results

- Accurate finger movement replication  
- Stable wireless range: 20–30 m  
- Response time < 50 ms  
- Reliable performance  

---

## 📱 Applications

- Prosthetic hands  
- Rehabilitation systems  
- Human–machine interface  
- Robotics research  
- Educational projects  

---

## ✅ Advantages

- Low cost  
- Wireless control  
- Real-time response  
- Portable design  
- Easy to modify  

---

## ⚠️ Limitations

- Limited wireless range  
- Requires calibration  
- Sensitive to noise  

---

## 🔮 Future Scope

- Mobile app control  
- AI gesture recognition  
- Haptic feedback  
- Cloud monitoring  
- Thumb integration  

---

## 📚 References

- ESP32 Datasheet – Espressif  
- Arduino Documentation  
- ESP-NOW Programming Guide  
- Robotics Sensor Technology  

---

## 🏁 Conclusion

This project demonstrates a wireless robotic hand using ESP32 and flex sensors.  
It provides a low-cost, efficient, and scalable solution for prosthetic and robotic applications.

---

## 👨‍💻 Author

**Project Name:** Robotic Arm : EXOGENESIS  
Developed By HARSHVARDHAN SHAH
