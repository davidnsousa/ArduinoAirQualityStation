# Air Quality Station

Arduino air quality station that collects and logs temperature, humidity, GPS and CO2 equivalent data to a file in an SD card. The code was developed for an educational activity as part of [GeoAcademy Project](https://geoacademy.eu), an EU-funded project promoting geospatial and environmental learning through hands-on activities. This README file provides information about the components, libraries, wiring instructions, and calibration steps.

## Air quality data logger

### Components Used

- **AM2302 Temperature & Humidity Sensor** to measure ambient temperature and humidity.
- **MQ-135 Gas Sensor** to measure air quality (CO2 equivalent concentration).
- **GPS Module** to fetch latitude, longitude, altitude and real-time date/time.
- **SD Card Module** to logs data to a file.
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

