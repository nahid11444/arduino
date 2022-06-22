#define sensor 2


void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);

}

void loop() {
  bool value = digitalRead(sensor);
  if (value == 1) {
    Serial.println("hit");
    delay(500);
  }


}
