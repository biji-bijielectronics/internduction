
int IRpin = A0;                                  
int playState;
void setup() {
  Serial.begin(9600);                             
}

void loop() {
  /* 
For information about converting volts and calculating distance from the sensor's please visit
http://luckylarry.co.uk/arduino-projects/arduino-using-a-sharp-ir-sensor-for-distance-calculation/
*/

  float volts = analogRead(IRpin)*0.0048828125;  
  float distance = 65*pow(volts, -1.10);     

	// we use playstate to detect when the distance crosses the border, so the music doesn't start over every 100ms

  if (distance <40){
    if(playState == 0){
      playState = 1;
      Serial.println("ON");
    }                      
  }
  else {
    if(playState == 1){
      playState = 0;
      Serial.println("OFF");
    }  
  }
 
  delay(100);                                     
}