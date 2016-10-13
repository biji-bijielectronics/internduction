int xValue = 0;
int yValue = 0;
int zValue = 0;

const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

int prevxValue = 0;
int prevyValue = 0;
int prevzValue = 0;
int diffy = 0;
int diffz =0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (13, OUTPUT);
}

void loop() {
// put your main code here, to run repeatedly:
xValue = analogRead(xPin);
yValue = analogRead(yPin);
zValue = analogRead(zPin);

diffy = prevyValue - yValue;

if(diffy <0){
  diffy = -diffy;
}
diffz = prevzValue - zValue;
if (diffz <0){
  diffz = -diffz;
}

if (diffy >= 10 || diffz>=10) {
  Serial.println("SHAKE");
  digitalWrite(13, HIGH);  
}
else {Serial.println("Calm");
digitalWrite(13, LOW);
}
delay(500);
prevyValue = yValue;
prevzValue = zValue;
}
