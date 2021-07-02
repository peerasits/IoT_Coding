#include <SoftwareSerial.h>
#include "VirtuinoCM.h"
SoftwareSerial espSerial =  SoftwareSerial(2,3);


const char* ssid = "dlink";
const char* password = "porome11";
#define DEBUG 0

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  connectToWiFiNetwork();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connectToWiFiNetwork(){
    Serial.println("Connecting to "+String(ssid));
    
    espSerial.println("AT+GMR");       // print firmware info
    waitForResponse("OK",1000);
    espSerial.println("AT+CWMODE=1");  // configure as client
    waitForResponse("OK",1000);
    espSerial.print("AT+CWJAP=\"");    // connect to your WiFi network
    espSerial.print(ssid);
    espSerial.print("\",\"");
    espSerial.print(password);
    espSerial.println("\"");
    waitForResponse("OK",10000);   
}

boolean waitForResponse(String target1,  int timeout){
    String data="";
    char a;
    unsigned long startTime = millis();
    boolean rValue=false;
    while (millis() - startTime < timeout) {
        while(espSerial.available() > 0) {
            a = espSerial.read();
            if (DEBUG) Serial.print(a);
            if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            rValue=true;
            break;
        } 
    }
    return rValue;
}
