# 🌱 Arduino Plant Monitoring System

<div align="center">

**A personal IoT plant care solution**


*An open-source, janky-but-functional plant monitoring system*


</div>

---

## 📖 About

This is my personal plant monitoring system project. Yes, it's a bit "janky" – but it works! Basic coding knowledge is helpful but not required. I'm always looking for contributors and improvements.

> **🤝 Contributions Welcome!** Have ideas? Found a bug? Want to improve the code? Please reach out!

---

## 🚀 Getting Started

### Prerequisites

#### Software
- **Arduino IDE** - [Download Here](https://www.arduino.cc)

#### Hardware Required

| Component | Description | Link |
|-----------|-------------|------|
| 🎛️ **Microcontroller** | Raspberry Pi Pico W/WH or Arduino (~$10) | [Amazon Link](https://a.co/d/4aHICb4) |
| 🍞 **Breadboard** | Solderless breadboard (recommended for beginners) | - |
| 🔌 **Jumper Wires** | For breadboard connections | - |
| 🌍 **Soil Sensor** | Corrosion-resistant capacitive sensor ⚠️ | [See below](#sensor-warning) |

> **💡 Pro Tip:** Get a Pico WH model – the "H" means headers are pre-soldered, making it plug-and-play!

---

### ⚠️ Sensor Warning

**DO NOT use cheap resistive sensors for long-term projects!**

❌ **Avoid:** [Cheap oxidizing sensors](https://a.co/d/iOuQ6Mj) – These work for ~1 week before corroding

✅ **Use:** [Corrosion-resistant capacitive sensors](https://a.co/d/7zGgF1j) – Built for longevity

---

## 🔧 Optional Components

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

## 📞 Contact me

📧 Email: [zPiProjects@gmail.com](mailto:zPiProjects@gmail.com)

---

## 🎯 Project Status

| Feature | Status |
|---------|--------|
| Soil Moisture Monitoring | ✅ Working |
| Automatic Watering | 🚧 In Progress |
| MQTT Integration | 📋 Planned |
| Web Dashboard | 💡 Idea Stage |


---

<div align="center">





