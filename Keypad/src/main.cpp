#include <Arduino.h>
#include <ESP8266WiFi.h>        
#include <PubSubClient.h>
#include <Keypad.h>

//WiFi info
const char* ssid     = "SSID";         // SSID
const char* password = "PASSPHRASE";     // Passphrase

//MQTT info
const char* mqttServer = "MQTTSERVER"; //MQTT Server
const int mqttPort = 1883; //MQTT Port
const char* mqttUser = "MQTTUSER"; //MQTT User
const char* mqttPassword = "MQTTPASS"; //MQTT Password

//Keypad info
const char sendKey = '*'; //Keypress to initialize send to MQTT
const byte n_rows = 4;
const byte n_cols = 4;

char keys[n_rows][n_cols] = { //Define values of keys
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','P','D'}
};

byte colPins[n_rows] = {D3, D2, D1, D0}; //Define row pins
byte rowPins[n_cols] = {D7, D6, D5, D4}; //Define column pins

Keypad Keypad1 = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols);
String fullKey;
char KeyMQTT[50];
WiFiClient espClient;
PubSubClient mqttclient(espClient);

  void wificn () {               //Connect to WiFi
    if(WiFi.status() != WL_CONNECTED) {
     WiFi.begin(ssid, password);             
     Serial.print("Connecting to ");
     Serial.print(ssid); Serial.println(" ...");

     int i = 0;
     while (WiFi.status() != WL_CONNECTED) { 
     delay(1000);
     Serial.print(++i); Serial.print(' ');
      }
     Serial.println('\n');
     Serial.println("Connection established!");  
     Serial.print("IP address:\t");
     Serial.println(WiFi.localIP());        
   
  }    
 }

void mqttcn () {              //Connect to MQTT
        mqttclient.setServer(mqttServer, mqttPort);
   
    while (!mqttclient.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (mqttclient.connect("Keypad Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
      mqttclient.loop();
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(mqttclient.state());
      delay(2000);
 
    }
    mqttclient.publish("keypad/LWT", "Online");
    }
}
void setup() {
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');
  wificn();
  mqttcn();
  
}

void loop() {
    char Key1 = Keypad1.getKey();
    if(Key1 == sendKey) {
     fullKey.toCharArray(KeyMQTT,fullKey.length()+1);
     mqttclient.publish("keypad/KEY", KeyMQTT);
     Serial.print("Sent key: ");
     Serial.println(fullKey);
     fullKey = "";
    } else if (Key1 != NULL){
     fullKey += Key1;
     Serial.print("Current keys: ");
     Serial.println(fullKey);
 
  }
  if(WiFi.status() != WL_CONNECTED) {
      wificn();
  }
  if(!mqttclient.loop()) {
      mqttcn();
  }
}
  


