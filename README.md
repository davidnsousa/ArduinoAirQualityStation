# Air Quality Station

Arduino air quality station that collects and logs temperature, humidity, GPS and CO2 equivalent data to a file in an SD card. The code was developed for an educational activity as part of [GeoAcademy Project](https://geoacademy.eu), an EU-funded project promoting geospatial and environmental learning through hands-on activities. This README file provides information about the components, libraries, wiring instructions, and calibration steps for two versions of the Air Quality Station. One for data logging using an SD card shield, and another one for real-time-visualization using an LCD display.

# Index

- [Air Quality Station](#air-quality-station)
  - [Air quality data logger](#air-quality-data-logger)
    - [Components Used](#components-used)
    - [Libraries Used](#libraries-used)
    - [Wiring Instructions](#wiring-instructions)
      - [AM2302 (Temperature & Humidity Sensor)](#am2302-temperature--humidity-sensor)
      - [MQ-135 (Air Quality Sensor)](#mq-135-air-quality-sensor)
      - [NEO-6M GPS module](#neo-6m-gps-module)
      - [HW-169 Data Logger Shield (SD Card Module)](#hw-169-data-logger-shield-sd-card-module)
    - [MQ-135 Sensor Calibration](#mq-135-sensor-calibration)
    - [Data Logging Format](#data-logging-format)
  - [Air quality real-time data visualization](#air-quality-real-time-data-visualization)
    - [Components Used](#components-used-1)
    - [Libraries Used](#libraries-used-1)
    - [Wiring Instructions](#wiring-instructions-1)
      - [AM2302 (Temperature & Humidity Sensor)](#am2302-temperature--humidity-sensor-1)
      - [MQ-135 (Air Quality Sensor)](#mq-135-air-quality-sensor-1)
      - [NEO-6M GPS module](#neo-6m-gps-module-1)
      - [LCD keypad shield SKU DFR0009](#lcd-keypad-shield-sku-dfr0009)
    - [MQ-135 Sensor Calibration](#mq-135-sensor-calibration-1)
    - [Usage](#usage)

## Air quality data logger

This version of the Air Quality Station will write the collected data to an SD card, but does not allow real-time visualization, except through the Arduino Serial monitor when it is connected through USB.

[Code](Data_logger.ino)

### Components Used

- **AM2302 Temperature & Humidity Sensor** to measure ambient temperature and humidity.
- **MQ-135 Gas Sensor** to measure air quality (CO2 equivalent concentration).
- **GPS NEO-6M Module** to fetch latitude, longitude, altitude and real-time date/time.
- **HW-169 Data Logger Shield (SD Card Module)** to log data to a file.
- **Arduino Board** UNO Rev3 to run the code and connect peripherals.
- **Other**: jumper wires and breadboard (if you are not prototyping directly in SD card shield).

### Libraries Used

- **AM2302-Sensor** by Frank Haefele for interfacing with the AM2302 sensor.  
- **MQ135** by GeorgeK for reading and calibrating the MQ-135 sensor.  
- **TinyGPSPlus** by Mikal Hart for parsing GPS data.  
- **SD** by Arduino for SD card file operations.

> Install all libraries via the Arduino Library Manager

### Wiring Instructions

#### AM2302 (Temperature & Humidity Sensor)

| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| AOUT       | D7        |

#### MQ-135 (Air Quality Sensor)

| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| AOUT       | A2          |

#### NEO-6M GPS module

| Module Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| TX         | D4          |
| RX         | D3          |

#### HW-169 Data Logger Shield (SD Card Module)

Simply fit the shield on top of your Arduino 

### MQ-135 Sensor Calibration

To get accurate air quality readings, calibrate the MQ-135 sensor:

1. **Burn-in Period:**  
   Run the sensor for 12–24 hours to stabilize readings.

2. **Obtain RZERO:**  
   - Open `File > Examples > MQ135 > MQ135` in Arduino IDE.  
   - Upload and run the sketch.  
   - Note the `RZERO` value in the Serial Monitor.

3. **Set RZERO in Code:**  
   Replace the default `#define RZERO 30` with your calibrated value:

   ```c++
   #define RZERO <your_calibrated_value>
   ```

4. **Calibrate in Clean Air:**  
   Perform calibration in a clean air environment for best accuracy.

### Data Logging Format

Data is saved to the SD card in CSV format:

```
YYYY-MM-DD HH:MM:SS,latitude,longitude,altitude(m),temperature(C),humidity(%),ppm
``` 

## Air quality real-time data visualization

This version of the Air Quality Station will output the data to the LCD display, but does not allow data logging.

[Code](Real-time_visualization.ino)

### Components Used

- **AM2302 Temperature & Humidity Sensor** to measure ambient temperature and humidity.
- **MQ-135 Gas Sensor** to measure air quality (CO2 equivalent concentration).
- **GPS NEO-6M Module** to fetch latitude, longitude, altitude and real-time date/time.
- **LCD keypad shield SKU DFR0009** to display the data.
- **Arduino Board** UNO Rev3 to run the code and connect peripherals.
- **Other**: jumper wires and breadboard (if you are not prototyping directly in SD card shield).

### Libraries Used

- **AM2302-Sensor** by Frank Haefele for interfacing with the AM2302 sensor.  
- **MQ135** by GeorgeK for reading and calibrating the MQ-135 sensor.  
- **TinyGPSPlus** by Mikal Hart for parsing GPS data.

> Install all libraries via the Arduino Library Manager

### Wiring Instructions

#### AM2302 (Temperature & Humidity Sensor)

| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| AOUT       | D13        |

#### MQ-135 (Air Quality Sensor)

| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| AOUT       | A2          |

#### NEO-6M GPS module

| Module Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| TX         | D2          |
| RX         | D3          |

#### LCD keypad shield SKU DFR0009

Simply attach the shield onto the Arduino board 

### MQ-135 Sensor Calibration

To get accurate air quality readings, calibrate the MQ-135 sensor:

1. **Burn-in Period:**  
   Run the sensor for 12–24 hours to stabilize readings.

2. **Obtain RZERO:**  
   - Open `File > Examples > MQ135 > MQ135` in Arduino IDE.  
   - Upload and run the sketch.  
   - Note the `RZERO` value in the Serial Monitor.

3. **Set RZERO in Code:**  
   Replace the default `#define RZERO 30` with your calibrated value:

   ```c++
   #define RZERO <your_calibrated_value>
   ```

4. **Calibrate in Clean Air:**  
   Perform calibration in a clean air environment for best accuracy.

### Usage

By long pressing the buttons, you can display specific information on the LCD screen: pressing Left shows air quality (ppm) readings, Up displays the GPS date and time, Down shows the GPS location including latitude, longitude, and altitude, and Right presents the temperature and humidity values. 
