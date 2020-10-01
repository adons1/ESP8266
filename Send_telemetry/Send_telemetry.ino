#include "ESP8266WiFi.h"

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <string>
#include <WiFiClient.h>

const char* ssid = "Vladimirsky central inc"; //Enter SSID
const char* password = "kartoshka0"; //Enter Password

int Random_Value(){
  srand (time(NULL));

  
  int iSecret = rand() % 10 + 1;
  return iSecret;
}

void setup(void)
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
     digitalWrite(LED_BUILTIN, LOW); 
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() 
{
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    http.begin(client, "http://192.168.1.177:3000/data.json");  // HTTP
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    Serial.print("[HTTP] GET...\n");

    
    int iSecret=Random_Value();
    String httpRequestData ="telemetry="+String(iSecret);
    int httpCode = http.POST(httpRequestData);
    String payload;
    Serial.println(httpCode);
    if (httpCode > 0) {

        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
          
        payload = http.getString();
        Serial.println(payload);
          
        http.end();
    } 
    else 
    {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  

  delay(5000);
  }
}
