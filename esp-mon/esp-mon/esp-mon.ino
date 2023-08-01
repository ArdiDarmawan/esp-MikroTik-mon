#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "isikan ssid wifi"
#define STAPSK  "password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server;

String 
s_data1       = "",
s_data2       = "",
s_data3       = "",
s_data4       = "",
s_data5       = "";


void setup() {
    
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
 
    server.on("/body", handleBody);
 
    server.begin();
    Serial.println("Menunggu Data");
}

void loop() {
 server.handleClient();
 
}
 
void handleBody() {
      if (server.hasArg("plain")== false){ 
            server.send(200, "text/plain", "No Data");
            return;
      }
        String data = server.arg("plain");
        DynamicJsonDocument doc(512);
        DeserializationError error = deserializeJson(doc,data);
        if(!error){
          if(doc.containsKey("data1")){
             String data1 = doc["data1"];         
             String data2 = doc["data2"]; 
             String data3 = doc["data3"];
             String data4 = doc["data4"];
             String data5 = doc["data5"];
             s_data1 = data1;
             s_data2 = data2;
             s_data3 = data3;
             s_data4 = data4;
             s_data5 = data5;
             server.send(200, "application/json", "{\"status\" : \"ok\"}");
       
            server.send(200, "text/plain", data);
            Serial.print("Identity       : "); Serial.println(s_data1); 
            Serial.print("Uptime         : "); Serial.println(s_data2);
            Serial.print("CPU Load       : "); Serial.println(s_data3+"%");
            Serial.print("Upload         : "); Serial.println(s_data4+"Mbps");
            Serial.print("Download       : "); Serial.println(s_data5+"Mbps");
          }}
}