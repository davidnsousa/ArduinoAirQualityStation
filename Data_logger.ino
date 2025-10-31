/*
 *  Air Quality Station
 *  -------------------
 *  Reads temperature, humidity, air quality (CO2 equivalent), and GPS data,
 *  then logs them to an SD card.
 *
 *  This code was developed for an educational activity as part of
 *  https://geoacademy.eu, an EU-funded project promoting geospatial and
 *  environmental learning through hands-on activities.
 *
 *  Wiring:
 *    AM2302: VCC → 5V, GND → GND, DATA → D7
 *    MQ135 : VCC → 5V, GND → GND, AOUT → A2
 *    GPS   : VCC → 5V, GND → GND, TX → D4, RX → D3
 *    SD Card: CS → D10 (SPI interface)
 *
 *  Output format (CSV line per record):
 *    YYYY-MM-DD HH:MM:SS,latitude,longitude,altitude,temperature,humidity,ppm
 *
 *  MQ135 Calibration:
 *    1) First, open File > Examples > MQ135 > MQ135 in the Arduino IDE and run
 *       the example sketch to read the RZERO value for your sensor.
 *    2) The sensor requires a 12–24 hour burn-in period for stable readings.
 *    3) After burn-in and obtaining the calibrated RZERO from the example, replace
 *       the RZERO definition in this code with that calibrated value.
 */


#include <AM2302-Sensor.h>
#include <MQ135.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

// Connect AM2302
#define PIN_AM2302 7
AM2302::AM2302_Sensor am2302{PIN_AM2302};

// Connect MQ-135 and define calibrated RZERO
#define PIN_MQ135 A2
#define RZERO 30
MQ135 mq135_sensor(PIN_MQ135,RZERO);

// Connect GPS
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// Connect SD card
const int chipSelect = 10;

// Setup
void setup() {
   
   // Start Serial
   while (!Serial) {
      yield();
   }
   Serial.begin(9600);

   // Start AM2302
   if (am2302.begin()) {
      delay(3000);
   }

   // Start GPS
   ss.begin(GPSBaud);

   // Start SD card
   SD.begin(chipSelect);
}

// Data collection
void loop() {

   String dataString = "";

   // Read GPS data if available
   if (ss.available()) {
      gps.encode(ss.read());
   }

  // Only print when a new GPS fix is available
   if (gps.location.isUpdated() && gps.location.isValid() && 
      gps.date.isValid() && gps.time.isValid()) {

      // Date
      dataString += String(gps.date.year()) + "-";
      dataString += String(gps.date.month()) + "-";
      dataString += String(gps.date.day()) + " ";

      // Time (UTC)
      dataString += String(gps.time.hour() < 10 ? "0" : "") + String(gps.time.hour()) + ":";
      dataString += String(gps.time.minute() < 10 ? "0" : "") + String(gps.time.minute()) + ":";
      dataString += String(gps.time.second() < 10 ? "0" : "") + String(gps.time.second()) + ",";

      // Location
      dataString += String(gps.location.lat(),6) + ",";
      dataString += String(gps.location.lng(),6) + ",";
      dataString += String(gps.altitude.meters()) + ",";

      // Temperature and Humidity
      am2302.read();
      dataString += String(am2302.get_Temperature()) + ",";
      dataString += String(am2302.get_Humidity()) + ",";

      // PPM
      dataString += String(mq135_sensor.getPPM());

      // Output to SD card
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      if (dataFile) {
         dataFile.println(dataString);
         dataFile.close();
         // print to the serial port too:
         Serial.println(dataString);
      }
      else {
         Serial.println("error opening datalog.txt");
      }

      delay(1000);
  }
}
