#include <SD.h>
#include <SPI.h>

int CS_PIN = 10;
long interval = 2000;
long previousMillis = 0;

int xValue = 0;
int yValue = 0;
int zValue = 0;

const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

int prevxValue = 0;
int prevyValue = 0;
int prevzValue = 0;

String state;

int diffy = 0;
int diffz =0;

int brightness = 0;
int fadeAmount = 5;

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
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (9, OUTPUT);
initializeSD();

}

void writeToSD(String data) {
  

 File dataFile = SD.open("state.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    // print to the serial port too:
    Serial.println(data);
  }
}
void loop() {
// put your main code here, to run repeatedly:

xValue = analogRead(xPin);
yValue = analogRead(yPin);
zValue = analogRead(zPin);

unsigned long currentMillis = millis();



if (currentMillis - previousMillis>interval){
  previousMillis = currentMillis;
  diffy = prevyValue - yValue;
  
if(diffy <0){
  diffy = -diffy;
}
diffz = prevzValue - zValue;
if (diffz <0){
  diffz = -diffz;
}

if (diffy >= 10 || diffz>=10) {
  while (brightness <= 255) {  
   analogWrite(9, brightness);
   brightness = brightness + fadeAmount;
   delay(30);
  }
  
  state = "Shake";
  
}
else {
  
  while (brightness >= 0) {  
   analogWrite(9, brightness);
   brightness = brightness - fadeAmount;
   delay(30);
  }

  state = "Calm";
}

state = state + "\t";
  writeToSD(state);
  
prevyValue = yValue;
prevzValue = zValue;
}

}
