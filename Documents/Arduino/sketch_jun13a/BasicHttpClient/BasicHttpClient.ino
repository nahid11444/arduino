#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

const char* ssid="nahidwifi";
const char* password = "11712135";

#define sensor 5
unsigned long mytime;
int c=0;
void setup() 
{
     Serial.begin(115200);
     pinMode(sensor,INPUT);
     
      WiFi.begin(ssid,password);
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }
      Serial.println("Wifi Connected Success!");
      Serial.println(WiFi.localIP() );
      Serial.print("Connecting");
      Serial.print("Wifi connecting to ");
      Serial.println( ssid ); 

  }

void loop() 
{ 
  mytime = millis();
  if(mytime < 100000){
       bool value = digitalRead(sensor);
       if (value == 1){
        Serial.println("hit");
        c++;
        delay(500);  
            
       }
  }
  Serial.println("Total hit:");
  Serial.print(c);
}
