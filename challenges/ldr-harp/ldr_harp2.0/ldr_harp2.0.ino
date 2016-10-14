//IRsharp
#include <SharpIR.h>
//RTC
#include <RTClib.h>
#include <Wire.h>
#define NUM_READINGS 20
//SD
#include <SD.h>
#include <SPI.h>

int IRpin = A0;                                  
boolean playState;

// IR Sharp sensor
SharpIR sensor(GP2Y0A02YK0F, A0);

// Real Time Clock object
RTC_DS3231 rtc;

//Clock pin for SD card module
int CS_PIN = 10;
int interval = 200;



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

void setup() {
  Serial.begin(9600);

  rtc.begin();
  initializeSD();
}

void writeToSD(String data) {

 File dataFile = SD.open("KotPidr.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
  }
}



void loop() { 
  int distance = sensor.getDistance(); 

	// we use playstate to detect when the distance crosses the border, so the music doesn't start over every 100ms

  if (distance < 40) {
    if (playState) {
      playState = false;
      Serial.println("ON");
      
      String hour =  String(rtc.now().hour());
      String minute = String(rtc.now().minute());
      String sec = String(rtc.now().second());

      String start = hour + ":" + minute  + ":" + sec  + "\t" + "ON";
      
      writeToSD(start);
      
      delay(interval);
    }                      
  }
  else {
    if (!playState) {
      playState = true;
      Serial.println("OFF");

      String hour =  String(rtc.now().hour());
      String minute = String(rtc.now().minute());
      String sec = String(rtc.now().second());

      String finish = hour + ":" + minute  + ":" + sec  + "\t" + "OFF";
      writeToSD(finish);
      delay(interval);
    }  
  }

  

  Serial.println(distance);                                    
  delay(interval);
}




