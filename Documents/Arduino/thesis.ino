#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialGPS(4, 5); 

SoftwareSerial neogps;

TinyGPSPlus gps;

unsigned long previousMillis = 0;
long interval = 6000;


void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
 

  //Begin serial communication with Arduino and SIM800L
  neogps.begin(9600);

  Serial.println("Initializing...");
  //delay(10000);
  
}

void loop()
{
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
       previousMillis = currentMillis;
       sendGpsToServer();
    }
}

int sendGpsToServer()
{
    //Can take up to 60 seconds
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 2000;){
      while (neogps.available()){
        if (gps.encode(neogps.read())){
          newData = true;
          break;
        }
      }
    }
  
    //If newData is true
    if(newData){
      newData = false;
      
      String latitude, longitude;
      float altitude;
      unsigned long date, time, speed, satellites;
  
      latitude = String(gps.location.lat(), 6); // Latitude in degrees (double)
      longitude = String(gps.location.lng(), 6); // Longitude in degrees (double)
      altitude = gps.altitude.meters(); // Altitude in meters (double)
      date = gps.date.value(); // Raw date in DDMMYY format (u32)
      time = gps.time.value(); // Raw time in HHMMSSCC format (u32)
      speed = gps.speed.kmph();
      
      Serial.print("Latitude= "); 
      Serial.print(latitude);
      Serial.print(" Longitude= "); 
      Serial.println(longitude);
      Serial.print(" Time= "); 
      Serial.println(time);
      Serial.print("Date= "); 
      Serial.println(date);
      Serial.print("Marching speed= "); 
      Serial.println(speed);
      //if (latitude == 0) {return 0;}
  }
  return 1;    
}
