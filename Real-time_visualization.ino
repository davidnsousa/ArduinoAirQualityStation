/*
 *  Air Quality Station
 *  -------------------
 *  Reads temperature, humidity, air quality (CO2 equivalent), and GPS data,
 *  then displays in a LCD screen keypad shield.
 *
 *  This code was developed for an educational activity as part of
 *  https://geoacademy.eu, an EU-funded project promoting geospatial and
 *  environmental learning through hands-on activities.
 *
 *  Wiring:
 *    AM2302: VCC → 5V, GND → GND, DATA → D13
 *    MQ135 : VCC → 5V, GND → GND, AOUT → A2
 *    GPS   : VCC → 5V, GND → GND, TX → D2, RX → D3
 *    LCD RS → D8
 *    LCD E  → D9
 *    LCD D4 → D4
 *    LCD D5 → D5
 *    LCD D6 → D6
 *    LCD D7 → D7
 *    Buttons → A0
 *    Backlight → D10
 *
 *  Usage
 *    Long press the LCD Keypad buttons Left, Up, Down and Right 
 *    Left :  Air quality
 *    Up   :  GPS date and time
 *    Down :  GPS Location (Latitude, Longitude, Altitude)
 *    Right:  Temperature and Humidity
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
#include <LiquidCrystal.h>

// Connect LCD
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Connect AM2302
#define PIN_AM2302 13
AM2302::AM2302_Sensor am2302{PIN_AM2302};

// Connect MQ-135 and define calibrated RZERO
#define PIN_MQ135 A2
#define RZERO 995
MQ135 mq135_sensor(PIN_MQ135,RZERO);

// Connect GPS
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// Update LCD display function
void updateDisplay(void (*displayFunc)(), unsigned long delayMs) {
   // continue to update the display
   while (true) {
      delay(delayMs);
      int x = analogRead (0);
      displayFunc();
      if (x < 1000) { // until any other button is pressed
         break;
      }
   }
}

// Retrieve GPS data function
void retrieveGPSdata() {
    int lastSecond = gps.time.second(); // remember current second
    while (true) {
        while (ss.available()) gps.encode(ss.read());
        // Stop only if we have a valid fix AND the second changed
        if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid() &&
            gps.time.second() != lastSecond) {
            break; // new data arrived
        }
    }
}

// Retrieve and display temperature and humidity data function
void displayTH() {
    auto status = am2302.read();
    lcd.clear();
    if (status == 0) { 
        lcd.setCursor(0,0); lcd.print("  Temp | Hum"); 
        lcd.setCursor(0,1); lcd.print(am2302.get_Temperature()); lcd.print("C | "); lcd.print(am2302.get_Humidity()); lcd.print("%");
    } else {
        lcd.setCursor(0,0); lcd.print("Fetching...");
    }
}

// Retrieve and display date and time data function
void displayDT() {
   retrieveGPSdata();
   lcd.clear();
   String  dateString = "";
   String  timeString = "";
   dateString += String(gps.date.year()) + "-";
   dateString += String(gps.date.month()) + "-";
   dateString += String(gps.date.day()) + " ";
   timeString += String(gps.time.hour() < 10 ? "0" : "") + String(gps.time.hour()) + ":";
   timeString += String(gps.time.minute() < 10 ? "0" : "") + String(gps.time.minute()) + ":";
   timeString += String(gps.time.second() < 10 ? "0" : "") + String(gps.time.second());
   lcd.setCursor(0,0); lcd.print("Date: "); lcd.print(dateString);
   lcd.setCursor(0,1); lcd.print("Time: "); lcd.print(timeString);
}

// Retrieve and display location data function
void displayL() {
   retrieveGPSdata();
   lcd.clear();
   String  latString = "";
   String  lonString = "";
   String  altString = "";
   latString += String(gps.location.lat(),2);
   lonString += String(gps.location.lng(),2);
   altString += String(gps.altitude.meters(),2);
   lcd.setCursor(0,0); lcd.print("Lat  | Lon | Alt ");
   lcd.setCursor(0,1); lcd.print(latString); lcd.print("|"); lcd.print(lonString); lcd.print("|"); lcd.print(altString);
}

// Retrieve and display air quality data function
void displayPPM() {
   lcd.clear();
   lcd.setCursor(0,0); lcd.print("CO2 (PPM)");
   lcd.setCursor(0,1); lcd.print(mq135_sensor.getPPM());
}

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

   // Start LCD
   lcd.begin(16,2);
   lcd.setCursor(0,0); lcd.print("Air Quality Stn");
   lcd.setCursor(0,1); lcd.print("Long press keys");
}

// Display Data
void loop() {
   int x;
   x = analogRead (0);
   if (x < 100)  { // Right key pressed
      updateDisplay(displayTH,1000);
   }        
   else if (x < 250) { // Up key pressed
      updateDisplay(displayDT,1000);
   }
   else if (x < 430) { // Down key pressed
      updateDisplay(displayL,1000);
   }
   else if (x < 800) { // Left key pressed
      updateDisplay(displayPPM,1000);
   }
   delay(100);
  }
