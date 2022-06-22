#include <ESP8266WiFi.h>

#include <WiFiClient.h>

const char* ssid="nahid";
const char* password = "11712135";
const char* host = "192.168.43.21";

unsigned long mytime;
#define sensor 5
#define sensor2 4

int c=0;
bool executed = false;


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
      Serial.print("Wifi connecting to ");
      Serial.println( ssid ); 

}

void loop() 
{ 
   mytime=millis();
  if(mytime<15000){
    {
       bool value = digitalRead(sensor);
       if(value == 1){
        Serial.println("hit");
        c++;
        delay(500);      
       }
    Serial.println("Total hit:");
  Serial.print(c);
  }

     {
       bool value = digitalRead(sensor2);
       if(value == 1){
        Serial.println("hit");
        c++;
        delay(500);      
       }
    Serial.println("Total hit:");
  Serial.print(c);
  }
  }


if(mytime>15000 && executed == false){
  executed=true;
  aFunction();
  }
}
void aFunction(){
  
 int Total_hit=c;
  WiFiClient client;
    const int httpPort = 8000;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
      Serial.print("connecting to ");
    Serial.println(host);
client.print(String("GET http://192.168.43.21/vkhs/send_to_admin.php?") + 
                          ("&Total_hit=") + Total_hit +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 10000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }

    Serial.println();
    Serial.println("closing connection");
  }
