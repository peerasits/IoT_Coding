#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "dlink"; // Enter your WiFi name
const char *password = "porome11";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.8.13";
const char *topic = "test";
const char *mqtt_username = "myhome";
const char *mqtt_password = "testtest";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
   pinMode(LED_BUILTIN, OUTPUT); 
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 Serial.print("Ip address : ");
 Serial.println(WiFi.localIP());
 
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp8266-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "hello emqx1234");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 if((char)payload[0] == '0'){
    digitalWrite(LED_BUILTIN,1);
 }else{
    digitalWrite(LED_BUILTIN,0);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 client.loop();
}
