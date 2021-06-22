const int pin = 7;
const int piezoPin = 4;


void setup() {
  Serial.begin(9600);
  pinMode(pin,INPUT);
  pinMode(piezoPin,OUTPUT);
  
}

void loop() {
  int val = digitalRead(pin);
  Serial.print(val);
  if(val==1)
    digitalWrite(piezoPin,1);
  else
    digitalWrite(piezoPin,0);
  delay(1000);

}
