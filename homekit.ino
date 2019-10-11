#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
//for IR
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
//for DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

// TCP server at port 80 will respond to HTTP requests
ESP8266WebServer server(80);
WiFiManager wifiManager;

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
const uint16_t DQ_pin = 2;  // DS18B20 Data pin: 2 (D4)
float temperature;      //The DS18B20 Temperature
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
OneWire oneWire(DQ_pin);
DallasTemperature sensors(&oneWire);

void airconditioner_on() {
  uint16_t rawData[307] = {3406, 1610,  490, 344,  486, 346,  486, 346,  486, 344,  486, 348,  484, 346,  486, 1176,  488, 346,  486, 346,  486, 346,  516, 316,  486, 346,  484, 346,  486, 378,  484, 346,  482, 320,  482, 380,  482, 350,  576, 1028,  514, 380,  454, 1174,  520, 346,  452, 382,  484, 348,  484, 348,  452, 380,  482, 316,  486, 378,  482, 350,  484, 348,  482, 316,  484, 1174,  488, 346,  486, 1174,  490, 1174,  490, 1176,  488, 380,  484, 1144,  488, 1176,  488, 378,  452, 378,  454, 1176,  518, 350,  482, 348,  452, 344,  486, 380,  452, 346,  486, 1172,  492, 344,  486, 1174,  490, 378,  452, 1174,  488, 346,  484, 1174,  490, 380,  452, 380,  452, 380,  452, 1174,  490, 380,  452, 1172,  492, 346,  486, 1174,  490, 1172,  490, 1176,  434, 1228,  434, 1230,  488, 380,  452, 380,  396, 436,  396, 1230,  434, 400,  432, 400,  432, 400,  430, 400,  432, 434,  396, 436,  396, 434,  396, 434,  398, 432,  398, 434,  396, 434,  396, 434,  396, 436,  396, 436,  396, 434,  396, 400,  428, 436,  396, 434,  396, 434,  396, 436,  396, 434,  396, 400,  432, 398,  432, 434,  396, 400,  430, 400,  432, 400,  432, 434,  398, 398,  432, 398,  432, 400,  430, 400,  430, 436,  396, 400,  430, 1226,  436, 436,  396, 434,  396, 434,  396, 400,  432, 434,  396, 434,  396, 434,  396, 434,  398, 434,  398, 434,  398, 432,  398, 1228,  434, 436,  384, 436,  496, 348,  396, 432,  398, 434,  396, 434,  398, 434,  396, 434,  396, 436,  396, 434,  396, 434,  396, 436,  396, 402,  430, 398,  432, 436,  396, 434,  396, 432,  398, 434,  396, 434,  398, 434,  398, 432,  452, 380,  396, 434,  396, 436,  396, 436,  450, 344,  488, 380,  450, 380,  446, 1176,  436, 434,  452, 346,  486, 1172,  490, 378,  452, 1172,  490, 380,  450};  // UNKNOWN 723229D5
  irsend.sendRaw(rawData, 307, 38);
  server.send(200, "text/plain");
}
void airconditioner_off() {
  uint16_t rawData[307] = {3428, 1590,  430, 434,  476, 324,  428, 436,  396, 404,  506, 324,  430, 434,  398, 1232,  510, 324,  506, 326,  430, 434,  398, 434,  396, 434,  398, 434,  398, 434,  398, 434,  398, 434,  396, 434,  398, 434,  396, 1236,  510, 322,  428, 1234,  510, 324,  506, 326,  428, 434,  472, 358,  474, 324,  506, 326,  428, 436,  398, 434,  396, 436,  396, 434,  396, 1234,  430, 404,  428, 1234,  432, 1232,  510, 1154,  430, 402,  428, 1234,  432, 1232,  430, 402,  430, 1232,  430, 404,  428, 402,  428, 402,  428, 404,  428, 404,  428, 404,  428, 1234,  432, 402,  428, 1232,  430, 402,  428, 1234,  430, 404,  428, 1234,  430, 404,  428, 404,  426, 406,  426, 1234,  430, 402,  428, 1234,  430, 402,  428, 1234,  430, 1232,  430, 1232,  430, 1234,  430, 1234,  430, 402,  428, 402,  428, 404,  428, 404,  428, 406,  426, 404,  428, 402,  428, 404,  426, 406,  426, 404,  428, 406,  426, 406,  426, 404,  428, 404,  428, 402,  428, 392,  424, 418,  428, 404,  428, 404,  428, 402,  430, 402,  428, 404,  426, 404,  426, 406,  426, 404,  428, 404,  426, 406,  424, 404,  426, 404,  426, 404,  428, 404,  426, 404,  426, 404,  426, 404,  428, 400,  428, 402,  428, 406,  426, 404,  426, 1232,  430, 404,  426, 406,  426, 406,  424, 404,  426, 404,  428, 402,  428, 404,  426, 404,  426, 404,  426, 404,  428, 404,  428, 1234,  430, 404,  426, 404,  428, 434,  396, 404,  424, 404,  426, 406,  426, 404,  426, 404,  426, 404,  428, 404,  428, 402,  428, 404,  428, 404,  428, 402,  428, 404,  428, 402,  428, 402,  428, 402,  428, 404,  428, 406,  426, 404,  428, 434,  398, 404,  426, 404,  428, 434,  396, 434,  398, 434,  396, 1232,  430, 1232,  432, 1230,  432, 1230,  432, 402,  428, 402,  428, 1230,  434, 400,  430};  // UNKNOWN 2B4BB77D
  irsend.sendRaw(rawData, 307, 38);
  server.send(200, "text/plain");
}
void fan() {
  irsend.sendNEC(0x0061D6807F);
  server.send(200, "text/plain");
}
void get_status() {
  if (digitalRead(4)) {
    server.send(200, "text/plain", "0");
  } else {
    server.send(200, "text/plain", "1");
  }
}
void get_temp() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  server.send(200, "text/plain", String(temperature-3));
}
void reset_wifi() {
  server.send(200, "text/plain");
  wifiManager.resetSettings();
}

void setup() {
  
  //Serial.begin(115200);
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  
  irsend.begin();

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  wifiManager.autoConnect("AutoConnectAP");

  //if you get here you have connected to the WiFi
  //Serial.println("connected...:)");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("homebridge")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Start TCP (HTTP) server
  server.on("/airconditioner/on", airconditioner_on);
  server.on("/airconditioner/off", airconditioner_off);
  server.on("/airconditioner/status", get_status);
  server.on("/fan/on", fan);
  server.on("/fan/off", fan);
  server.on("/status/temp", get_temp);
  server.on("/reset", reset_wifi);
  server.begin();
  Serial.println("TCP server started");
  //Temp sensor
  sensors.begin();
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  MDNS.update();
  server.handleClient();
}
