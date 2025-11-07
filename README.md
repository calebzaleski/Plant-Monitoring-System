<div align="center">

# Plant Monitoring System

**A personal IoT plant care solution**

*An open-source, janky but functional plant monitoring system*

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc)
[![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-A22846?style=for-the-badge&logo=Raspberry%20Pi&logoColor=white)](https://www.raspberrypi.org)

</div>



## 📖 About

This is my personal plant monitoring system project. Yes, it's a bit "janky" – but it works! It montiors the **tempature, humity and soil moisture, and it has a water pump.** This project is very beginner friendly and I suggest that you dont just follow the steps, but rather look though the code and try to understand everything. I tried to make it very simple and easy to navigate for this purpose. It can seem like its a big project, but with some time you can easily figure it out! **This project is completely safe for you home internet as it does not require any port forwarding or tampering with the network.**.

> **Contributions Welcome!** Have ideas? Found a bug? Want to improve the code? Please reach out to me through **<a href="mailto:zPiProjects@gmail.com" style="color: black;">Email</a>**


---

##  Getting Started

### Prerequisites

#### Gmail account
>Other accounts can be used but I have not tested them because Gmail is just so easy to set up.

#### Software
**[Arduino IDE](https://www.arduino.cc)**

#### Hardware Requirements

| Component | Description | Link |
|-----------|-------------|------|
|  **Microcontroller** | Raspberry Pi Pico W/WH or Arduino (~$10) | [Amazon](https://a.co/d/4aHICb4) |
|  **Soil Sensor** | Corrosion-resistant capacitive sensor ⚠️ | [Adafruit](https://www.adafruit.com/product/5587)) |
|  **Breadboard & Jumper Wires** | Solderless breadboard (recommended for beginners) | [Amazon](https://a.co/d/diuLBDd) |
|  **Push Button** | Manual email sending button | [Amazon](https://a.co/d/6T3IJLN) |
>  **I used a Pico W**

> **DO NOT use cheap resistive sensors for long-term projects!**

> **"H" means headers are pre-soldered**

### Optional Hardware and Software 

| Component | Description | Link |
|-----------|-------------|------|
|  **Water Pump** | 3V DC submersible pump, 1 meter vertical lift | [Adafruit](https://www.adafruit.com/product/4547) |
|  **MQTT Server** | Seperate Pi or Arduinio to run the MQTT server | [Eclipse Mosquitto](https://github.com/eclipse-mosquitto/mosquitto) |



---


##  Project Status

| Feature | Status |
|---------|--------|
| Soil Moisture Monitoring | ✅ Working |
| Daily Email Report | ✅ Working |
| MQTT Integration | ✅ Working |
| Automatic Watering | 🚿 Planned |
| Web Dashboard | 💡 Idea Stage |
| Lighting | 💡 Idea Stage |


---

##  Setup Guide

### Step 1: Setup

**1.1** Download **[Arduino IDE](https://www.arduino.cc)**

**1.2** Open Arduino IDE

**1.3** Plug in your Microcontroller to your computer.


### Step 2: Download/Clone the Repo
#### Method 1: Download ZIP

1. Go to the project page
2. Click the green **Code** button
3. Click **Download ZIP**
4. Find the ZIP in your Downloads folder
5. Right-click → **Extract All**

 #### Method 2: Clone & Open
 
   ```git clone https://github.com/calebzaleski/Ardunio-Plant-Project.git```

   then to update later: ```git pull```

>  Make sure you have git installed.

#### Open the .ino file in Ardunio IDE

### Step 3: Include the Libraries

#### Here we are going to include the libraries for the project

**3.1** Navigate to Library Manager in Arduino IDE by clicking the icon on the left with the books or by Sketch > Include Library > Manage Libraries. 

**3.2** Search for `ESP_mail_Client` by Mobizt and `PubSubClient` by Nick O'Leary and add both of them.

**3.3** Go to [Plant Sensor Library](https://github.com/monkmakes/mm_plant_monitor) click Code > download .ZIP

**3.4** Next in Arduino IDE, Sketch > Include Library > add .ZIP library, and navigate to the file you just downloaded.
>Sometimes it downloads in a folder so just compress it and add the ZIP.

### Step 4: Configuration

#### Here you will configure the project to your own needs.

**4.1** Navigate to `wifi_example.h` and then click the 3 dots on the right side and rename it to `wifi.h`

**4.2** Where it says ssid and password, put your network name and password inside of the ""

**4.3** Where it says `EMAIL_USER` and `EMAIL_APP_PASSWORD` put in your Gmail address and then your app specific password.
>Make sure you generate an app specific password, it will not work if you use your regular password [Google Passwords](https://support.google.com/accounts/answer/185833).
>since this is a plain text file, do not share it, you ***WILL*** expose your internet settings and Gmail details!


### Step 5: Connecting of the Pins

#### Here we will connect all the pins! Plan to spend some time doing this.
>make sure you have your breadboard and jumper wires ready.

>A *pinout* can be googled for Arduino's and Raspberry Pi's so you can figure out what pins I am refering 2.


<div style="display: flex; gap: 20px; align-items: flex-start;">

<div>

### Connections
<table>
<tr>
<td valign="top">


| TO | FROM |
|-----------|--------------|
|Button|GP3/5|
|Button|- on breadboard|
|Pico/Arduino 3V3(Out)|+ on breadboard|
|Pico/Arduino GND|- on breadboard|
|GP17/UARTO_RX/22|TX on Soil Sensor|
|GP16/UARTO_TX/21|RX on Soil Sensor|
|+ on Soil Sensor|+ on breadboard|
|GND on Soil sensor|- on breadboard|

</td>
<td valign="top">

<img width="600" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/511e66e1-5a49-4ff6-92a3-535e94c75150" />

</td>
</tr>
</table>

### Step 6: Set up MQTT server (Optional).

Im not going to walk you through how to do that here since that is optional, but I do have it set up to publish it to `Soil_Sensor/topic` Be sure to change the MQTT server in config.ino to match your server IP address.
> Use `mosquitto_sub -h 192.168.1.*** -t "Soil_Sensor/topic"` to check the readings or download and MQTT app on your phone.
> I have it set to publish every minute.


### Step 7: Setting daily check-ins and flashing.

**7.1** Navigate over to email.ino and find `const int scheduledHours[] = {7, 13, 18, 19, 21};` and `const int scheduledMinutes[] = {0, 0, 0, 0, 0};` Here you can replace the values. It is the 1st hour to the first minute and so on. If you want more or less check-ins make sure you change `for (int i = 0; i < 5; i++)` Replace the 5 with the # of check-ins

**7.2**
if you are ***not*** using a MQTT server, navigate to main.ino. In `void setup()` remove `connectMQTT();` and in `void loop()` remove
```
   connectMQTT():
    if (i == 600) {
      pushMQTT();
      i = 1;
    } 
    
    i++;
```


**7.3** Click the arrow pointing to the right or do `cmd + U` to upload your sketch to the microcontroller. Wait for it to finish flashing, uplug from your computer and plug into a long term power supply.

### CONGRATS YOU MADE IT TO THE END. PRESS THE BUTTON TO ADMIRE YOUR WORK!
>If you didnt recive an email when you pressed the button check your wiring and the serial controller.

---

 
##  Resources

- [Arduino Pico Documentation](https://arduino-pico.readthedocs.io/)
- [Ardunio IDE Documentation](https://www.arduino.cc/en/software/)
- [Capacitive Soil Sensor Guide](https://how2electronics.com/capacitive-soil-moisture-sensor-arduino/)
- [MQTT Setup Tutorial](https://randomnerdtutorials.com/esp8266-and-node-red-with-mqtt/)
  

---


</div>


