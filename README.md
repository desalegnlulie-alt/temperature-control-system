# Automatic Temperature Control System 🌡️❄️🔥

An embedded systems mini-project that continuously monitors environmental temperature and automatically triggers cooling or heating mechanisms based on predefined thresholds. 

This project was developed for the **Embedded Systems** course at **Addis Ababa Science and Technology University (AASTU)**.

## 🎯 Project Overview
The goal of this project is to design a closed-loop temperature control system. The system uses a temperature sensor to constantly monitor the environment. Based on the readings:
* **Cooling Mode:** When the measured temperature goes above the defined threshold, the system automatically activates a cooling fan.
* **Heating Mode:** When the measured temperature drops below the threshold, the system activates a heater.
* **Monitoring:** The current real-time temperature reading and system status are continuously displayed on an LCD screen.

## 🛠️ Software & Tools
* **IDE / Compiler:** MPLAB X IDE (using C programming)
* **Simulation Software:** Proteus Design Suite
* **Version Control:** Git & GitHub

## 🧩 Hardware Components (Simulated in Proteus)
* **Microcontroller:** (e.g., PIC16F877A or similar)
* **Temperature Sensor:** LM35 (or equivalent analog sensor)
* **Display:** 16x2 Alphanumeric LCD Display
* **Actuators:** DC Motor (representing the Cooling Fan) & Heating Element / LED Indicator (representing the Heater)

## ⚙️ System Logic
1. The microcontroller reads analog voltage from the temperature sensor.
2. The built-in ADC (Analog-to-Digital Converter) translates this voltage into a Celsius temperature value.
3. The value is evaluated against the programmed threshold.
4. Appropriate digital output pins are triggered high/low to control the fan and heater relays.
5. The LCD is updated with the string: `Temp: XX °C`

## 🚀 How to Run the Simulation

**1. Clone the repository:**
git clone https://github.com/yourusername/temperature-control-system.git
cd temperature-control-system

**2. Open the Code:**
* Open **MPLAB X IDE**.
* Navigate to `File > Open Project` and select the MPLAB project folder.
* Compile/Build the project to generate the `.hex` file.

**3. Run the Proteus Simulation:**
* Open the `.pdsprj` file using **Proteus**.
* Double-click on the Microcontroller in the schematic.
* Under "Program File", browse and select the compiled `.hex` file from the MPLAB output folder.
* Click the **Play (Run)** button at the bottom left of Proteus.
* Use the arrows on the simulated temperature sensor to increase or decrease the temperature and watch the Fan and Heater react!

## 👥 Developer
**Addis Ababa Science and Technology University (AASTU)**  
*College of Engineering | Dept. of Electromechanical Engineering*

* By Desalegn Lulie

**Course:** Embedded Systems
