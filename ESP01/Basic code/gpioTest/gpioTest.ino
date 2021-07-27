
//esp01 GPIO test
const int pinOut1 = 0;
const int pinOut2 = 2;


void setup() {
  pinMode(pinOut1,OUTPUT);
  pinMode(pinOut2,OUTPUT);

}

void loop() {

  digitalWrite(pinOut1,1);
  digitalWrite(pinOut2,2);
  delay(1000);
   digitalWrite(pinOut1,0);
  digitalWrite(pinOut2,0);
  delay(1000);

}
