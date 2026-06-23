IoT-Driven Dual-Microcontroller Smart Door Automation

This project is an integrated IoT-Based Smart Door Automation System featuring real-time state tracking, automated proximity detection, and an encrypted cloud manual override gateway.

System Architecture
Hardware Controller:Arduino UNO R3 handles the high-speed local logic (Ultrasonic sensor parsing, Servo movement, LED/Buzzer feedback).
Wi-Fi Gateway: NodeMCU ESP8266 handles the Blynk cloud synchronization and remote manual overrides.

Hardware Components
* Arduino UNO R3 & NodeMCU ESP8266
* HC-SR04 Ultrasonic Sensor
* TowerPro SG90 Servo Motor
* Active Buzzer & LEDs (Red/Green)

Key Features
1. Precise Proximity Detection: 15cm threshold for contactless entry.
2. Conflict-Free Cloud Override: A remote Blynk app button temporarily locks out the physical sensor to prevent hardware conflicts during manual control.
3. Instant Local Feedback: Polarized LEDs and acoustic alerts reflect the real-time physical status of the servo mechanism.
