#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;
SoftwareSerial SerialGPS(4, 5);

 bool exec = false;

unsigned long mytime;
 
const char* ssid = "nahid";
const char* password = "11712135";
const char* host = "192.168.107.229";

int year , month , date, hour , minute , second;
String DateString , TimeString , Latitude , Longitude;


WiFiServer server(8000);
void setup()
{
  Serial.begin(9600);
  SerialGPS.begin(9600);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());

}

void newf(){
  
  while (SerialGPS.available() > 0 && !exec){
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.date.isValid())
      {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
        DateString = '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
        DateString += '0';
        DateString += String(month);
        DateString += " / ";

        if (year < 10)
        DateString += '0';
        DateString += String(year);
      }

      if (gps.time.isValid())
      {
        TimeString = "";
        hour = gps.time.hour()+ 5; //adjust UTC
        minute = gps.time.minute();
        second = gps.time.second();
    
        if (hour < 10)
        TimeString = '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
        TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
        TimeString += '0';
        TimeString += String(second);
      }
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 8000;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    if (gps.location.isValid()){

        String mac = WiFi.macAddress();

        float lat = (gps.location.lat());
        float lng = (gps.location.lng());
    // This will send the request to the server
 client.print(String("GET http://host/thesis/send_data.php?") + 
                          ("&Latitude=") + lat+
                          ("&Longitude=") + lng+
                          ("&mac=") + String(mac) +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available() ) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }
            exec = true;

    Serial.println();
    Serial.println("closing connection");
    }

}
}
  void loop(){
      newf();
}



