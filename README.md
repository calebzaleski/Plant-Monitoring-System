<div align="center">

# Arduino Plant Monitoring System

**A personal IoT plant care solution**

*An open-source, janky but functional plant monitoring system*

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc)
[![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-A22846?style=for-the-badge&logo=Raspberry%20Pi&logoColor=white)](https://www.raspberrypi.org)

</div>

---

## 📖 About

This is my personal plant monitoring system project. Yes, it's a bit "janky" – but it works! Basic coding knowledge is helpful but not required. I'm always looking for contributors and improvements.

> **🤝 Contributions Welcome!** Have ideas? Found a bug? Want to improve the code? Please reach out to me through **<a href="mailto:zPiProjects@gmail.com" style="color: black;">Email</a>**
---

---

## 🚀 Getting Started

### Prerequisites

#### Software
**[Arduino IDE](https://www.arduino.cc)**

#### Hardware Requirements

| Component | Description | Link |
|-----------|-------------|------|
| 🎛️ **Microcontroller** | Raspberry Pi Pico W/WH or Arduino (~$10) | [Amazon](https://a.co/d/4aHICb4) |
| 🌍 **Soil Sensor** | Corrosion-resistant capacitive sensor ⚠️ | [Amazon](https://a.co/d/7zGgF1j) |
| 🍞 **Breadboard** | Solderless breadboard (recommended for beginners) | - |
| 🔌 **Jumper Wires** | For breadboard connections | - |

>  **I used a Pico W**

> **DO NOT use cheap resistive sensors for long-term projects!**

> **"H" means headers are pre-soldered, making it plug-and-play!**



## 🔧 Optional Hardware Pieces

### Automatic Watering System *(Coming Soon)*
- **3V DC Water Pump** - Submersible, 1 meter vertical
- [Adafruit Link](https://www.adafruit.com/product/4547)

### MQTT Server Setup *(Optional)*
Run an MQTT broker for wireless data transmission using any Raspberry Pi:
```
Compatible Models:
├── Raspberry Pi Zero (W/2W)
├── Raspberry Pi 1-4
└── Raspberry Pi 400
```

📦 **MQTT Server:** [Eclipse Mosquitto](https://github.com/eclipse-mosquitto/mosquitto)

---

## ⚡ Power Requirements

> **🔴 CRITICAL:** Insufficient power causes mysterious failures and hours of debugging frustration!

Ensure your Raspberry Pi or Arduino has:
- Adequate power supply (5V, 2.5A+ recommended for Pi)
- Quality USB cable (avoid cheap cables with voltage drop)
- Stable power source

---


## 🎯 Project Status

| Feature | Status |
|---------|--------|
| Soil Moisture Monitoring | ✅ Working |
| Dayily Email Report | ✅ Working |
| Automatic Watering | 🚧 In Progress |
| MQTT Integration | 📋 Planned |
| Web Dashboard | 💡 Idea Stage |

---

## 📋 Setup Guide

### Step 1: Install & Open **[Arduino IDE](https://www.arduino.cc)**
#### Plug in your Microcontroller to your computer.

### Step 2: Download/Clone the Repo
#### Method 1: Download ZIP

1. Go to the project page
2. Click the green **Code** button
3. Click **Download ZIP**
4. Find the ZIP in your Downloads folder
5. Right-click → **Extract All**

 #### Method 2: Clone
 
   `git clone https://github.com/calebzaleski/Ardunio-Plant-Project.git`

   then to update later: `git pull`

> make sure you have git installed and are in the right /cd

#### Open the .ino file in Ardunio IDE.

### Step 3: ...

---


## 📚 Resources

- [Arduino Pico Documentation](https://arduino-pico.readthedocs.io/)
- [Capacitive Soil Sensor Guide](https://how2electronics.com/capacitive-soil-moisture-sensor-arduino/)
- [MQTT Setup Tutorial](https://randomnerdtutorials.com/esp8266-and-node-red-with-mqtt/)

---


</div>


