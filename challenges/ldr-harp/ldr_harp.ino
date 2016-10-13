

// the setup routine runs once when you press reset:
int IRpin = A0;                                    

void setup() {
  Serial.begin(9600);                            
}

void loop() {
  // 5V/1024 = 0.0048828125   
  float volts = analogRead(IRpin)*0.0048828125;   
  float distance = 65*pow(volts, -1.10);         
  Serial.println(distance);                      
  delay(200);                                     
}