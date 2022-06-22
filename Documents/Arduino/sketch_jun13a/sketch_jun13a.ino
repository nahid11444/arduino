#include <ESP8266WiFi.h>
const char* ssid = "nahidwifi";
const char* password = "11712135";
// Arduino standard is GPIO13 but lolin nodeMCU is 2 http://www.esp8266.com/viewtopic.php?f=26&t=13410#p61332
WiFiServer server(80);
void setup() {
 Serial.begin(115200);

// Connect to WiFi network
 Serial.print("Connecting to ");
 Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");

// Start the server
 server.begin();
 Serial.println("Server started");

// Print the IP address
 Serial.print("Use this URL to connect: ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");

}

void loop() {
 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
 return;
 }

// Wait until the client sends some data
 Serial.println("new client");
 while(!client.available()){
 delay(1);
 }
 }
