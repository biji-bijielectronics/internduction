//Temp
#include <cactus_io_DS18B20.h>


//RTC
#include <RTClib.h>
#include <Wire.h>
#define NUM_READINGS 20
//SD
#include <SD.h>
#include <SPI.h>


int DS18B20_Pin = 9; //DS18S20 Signal pin on digital 9

// Create DS18B20 object for Temp sensor
DS18B20 ds(DS18B20_Pin);

RTC_DS3231 rtc; // Real Time Clock object

//Clock pin for SD card module
int CS_PIN = 10;
int interval = 2000;

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //initialise temp sensor
  ds.readSensor();

  // initialise real time clock
  rtc.begin();

  //initialise SD card
  initializeSD();

  
  //delay(2000);

}


void writeToSD(String data) {
  

 File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
  }

 // writeToFile(charBuf);


  //Serial.println(charBuf);

}

void loop() {

  ds.readSensor();
  float temp = ds.getTemperature_C();
  String hour =  String(rtc.now().hour());
  String minute = String(rtc.now().minute());
  String sec = String(rtc.now().second());

  String line = hour + ":" + minute  + ":" + sec  + "\t" + temp;

  writeToSD(line);

  delay(interval);
}


