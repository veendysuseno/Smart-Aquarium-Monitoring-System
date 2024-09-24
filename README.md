# Smart Aquarium Monitoring System

The **Smart Aquarium Monitoring System** is an IoT-based project designed to monitor and control water temperature, pH levels, and other environmental parameters in an aquarium. The system is integrated with the Blynk platform for real-time monitoring and notifications. The system controls the heater, fan, and buzzer based on sensor readings and notifies the user via the Blynk app if conditions go out of range.

## Features

- **Water Temperature Monitoring**: Measures the aquarium's water temperature and controls a heater and fan to keep the temperature within a safe range.
- **pH Monitoring**: Monitors the water's pH levels and alerts users when it goes beyond a defined range.
- **Buzzer Alerts**: Sounds an alarm when pH levels are abnormal.
- **Blynk App Integration**: Real-time data visualization and notifications using the Blynk app.

## Components

- **ESP8266**: The microcontroller used for connecting to WiFi and running the control logic.
- **pH Sensor**: For monitoring water acidity or alkalinity.
- **DS18B20 Temperature Sensor**: For reading water temperature.
- **Buzzer**: For sounding alarms when environmental conditions go out of the safe range.
- **Heater and Fan**: To control the water temperature automatically.
- **LCD I2C**: 16x2 LCD for displaying the current pH and temperature readings.

## Requirements

### Hardware

- ESP8266 (NodeMCU or similar)
- DS18B20 Temperature Sensor
- pH Sensor
- LiquidCrystal I2C (16x2)
- Buzzer
- Relay Module (to control heater and fan)
- Heater and Fan for temperature regulation
- Jumper wires and breadboard for prototyping

### Software

- **Arduino IDE**: For writing and uploading code to the ESP8266.
- **Blynk App**: For monitoring sensor data in real-time.

## Libraries

The following libraries are required for the project:

- **[Blynk Library](https://github.com/blynkkk/blynk-library)**: For integration with the Blynk IoT platform.
- **[ESP8266WiFi Library](https://github.com/esp8266/Arduino)**: For handling WiFi connection on the ESP8266.
- **[OneWire Library](https://www.pjrc.com/teensy/td_libs_OneWire.html)**: To communicate with the DS18B20 sensor.
- **[DallasTemperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)**: To handle temperature readings from the DS18B20 sensor.
- **[LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C)**: For controlling the I2C LCD.

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/smart-aquarium-monitoring-system.git
   ```

2. **Install the required libraries**:

   - Open Arduino IDE.
   - Go to **Sketch > Include Library > Manage Libraries**.
   - Search for the libraries listed above and install them.

3. **Configure the Blynk App**:

   - Download the Blynk app on your phone and create a new project.
   - Add widgets for displaying pH and temperature values.
   - Copy the **auth token** provided in the Blynk project setup and add it to the code in `char auth[]`.

4. **Configure your WiFi credentials**:
   In the code, replace the `ssid` and `pass` variables with your WiFi credentials:

   ```cpp
   char ssid[] = "YourWiFiSSID";
   char pass[] = "YourWiFiPassword";

   ```

5. Upload the code:
   - Connect your ESP8266 to the computer via USB.
   - Select the correct board (Tools > Board > NodeMCU 1.0) and the correct COM port.
   - Click on the Upload button.

## Usage

1. After uploading the code to the ESP8266, open the Serial Monitor to see the debug output.
2. The system will start reading the pH and temperature values.
3. The values will be displayed on the LCD and sent to the Blynk app for remote monitoring.
4. If the pH level goes beyond the range of 6-8, the buzzer will sound, and a notification will be sent to the Blynk app.
5. The heater and fan will automatically adjust based on the temperature values.

## Future Improvements

- Integration with cloud storage for long-term data logging.
- Adding more sensors for other water quality metrics (e.g., dissolved oxygen).
- Battery backup for the system in case of power outages.

## License

This project is licensed under the MIT License. See the LICENSE file for more information.
