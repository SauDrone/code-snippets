void setup() {
  Serial.begin(115200);

}

void loop() {
  //------------------------------------
  long a=micros();
  String message=String(1000)+String(1000)+String(1000)+String(1000)+ String(1000) + ".";
  Serial.print(message);
  long b=micros() -a;
  //-------------- [784,792] micro saniye
  delay(4);
  //Serial.print("Sure: ");
  //Serial.println(b);
}
