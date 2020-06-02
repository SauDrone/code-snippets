String coming_text;
int real_fl, real_fr, real_bl, real_br;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2);

}

void loop() {
  //------------------------------
  long a = micros();
  if (Serial.available()) {
    coming_text = Serial.readStringUntil('.');
    //gelecek paket: 0000000000000000 -> 16 karakter olmalı
    if (coming_text.length() == 16) {
      String fl = coming_text.substring(0, 4);
      int fl_ = fl.toInt();
      String fr = coming_text.substring(4, 8);
      int fr_ = fr.toInt();
      String bl = coming_text.substring(8, 12);
      int bl_ = bl.toInt();
      String br = coming_text.substring(12, 16);
      int br_ = br.toInt();
    }
    unsigned long n = micros() - a;
    //-------------- [1000,2000] micro saniye
    Serial.print("gecensure:");
    Serial.println(n);
  }



}
