#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define myPeriodic 60 //in sec Thingspeak
#define ONE_WIRE_BUS D4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float prevTemp = 0;
const char* server1 = "api.thingspeak.com";
String apiKey1 ="3C8PVHF697ZQO95Z";
const char* server2 = "maker.ifttt.com";
String apiKey2 = "bXvsYy0M4Sm72IA6rDErjQ";
String path ="/trigger/temp/with/key/" + apiKey2 + "?value1=";
const char* MY_SSID = "iptime_HN"; 
const char* MY_PWD = "qwerty1234!@";
int sent = 0;
void setup() {
  Serial.begin(115200);
  connectWifi();
}

void loop() {
  float temp;
  //char buffer[10];
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  //String tempC = dtostrf(temp, 4, 1, buffer);//handled in sendTemp()
  Serial.print(">>ThingSpeak");
  Serial.print("  ("+String(sent)+") Temperature: ");
  Serial.println(temp);
  
  //if (temp != prevTemp)
  //{
  //sendTemperatureTS(temp);
  //prevTemp = temp;
  //}
  
  sendTemperatureTS(temp);
  int count = myPeriodic/6;
  while(count--){
    temp = DS18B20.getTempCByIndex(0);
    Serial.print("==IFTTT");
    Serial.print("  ("+String(sent)+") Temperature: ");
    Serial.println(temp);
    sendTemperatureMaker(temp);
    delay(5000);
  }
}

void connectWifi()
{
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.begin(MY_SSID, MY_PWD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

void sendTemperatureTS(float temp)
{  
   WiFiClient client;
  
   if (client.connect(server1, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   Serial.println("WiFi Client connected to ThingSpeak");
   
   String postStr = apiKey1;
   postStr += "&field1=";
   postStr += String(temp);
   postStr += "\r\n\r\n";
   
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: " + apiKey1 + "\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   delay(500);
   
   }//end if
   sent++;
 client.stop();
}//end send


void sendTemperatureMaker(float temp)
{  
   WiFiClient client;
  
   if (client.connect(server2, 80)) { 
   Serial.println("WiFi Client connected to IFTTT");
   
   client.print("GET " + path + String(temp));
   client.print(" HTTP/1.1\r\n");
   client.print("Host: maker.ifttt.com\r\n"); 
   client.print("Connection: close\r\n\r\n");
   delay(500);
   
   }//end if
   sent++;
 client.stop();
}//end send
