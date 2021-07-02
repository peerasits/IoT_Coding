#include <SoftwareSerial.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//#include


#define TIMEOUT 5000 // mS
#define LED 5

SoftwareSerial mySerial(2, 3); // RX, TX
const int button = 11;
int button_state = 0;
const String wifiSSID = "dlink";
const String wifiPASS = "porome11";


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200);

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  initWiFi();

  /*
    SendCommand("AT+CWMODE=1", "OK");
    SendCommand("AT+CIFSR", "OK");
    SendCommand("AT+CIPMUX=1", "OK");
    SendCommand("AT+CIPSERVER=1,80", "OK");
  */
}

void initWiFi() {
  //Serial.println(SendCommand("AT", "OK"));
  Serial.println(SendCommand("AT+RST", "OK"));
  Serial.println(SendCommand("AT+CWMODE=1","OK"));
   Serial.println(SendCommand("AT+CIFSR", "OK"));
  Serial.println(SendCommand("AT+CIPMUX=1","OK"));
  Serial.println(SendCommand("AT+CIPSERVER=0","OK"));
  Serial.println(SendCommand("AT+CWJAP=\""+wifiSSID+"\",\""+wifiPASS+"\"", "OK"));

  
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  
}

boolean SendCommand(String cmd, String ack) {
  Serial.println(cmd);
  mySerial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return false;// ack blank or ack found
  return true;
}

boolean echoFind(String keyword) {
  byte current_char = 0;
  byte keyword_length = keyword.length();
  long deadline = millis() + TIMEOUT;
  String result = "";
  while (millis() < deadline) {
    while (mySerial.available()) {
      char ch = mySerial.read();
      if (ch >= 32)
        result += (String)ch;
    }
  }
  Serial.println(result);
  if (result.indexOf(keyword) != -1)
    return true;
  else
    return false;


}
