
  int yaw=1000,pitch=1000,roll=1000,throttle=1000; 
String coming_text;
int real_fl,real_fr,real_bl,real_br;
void setup()  
 {  

  
  Serial.begin(115200);
  Serial.setTimeout(2);
    

}

 
 void loop()  
 {  
  if(Serial.available()){
        
        coming_text = Serial.readStringUntil('.');
        //gelecek paket: 0000000000000000 -> 16 karakter olmalı
        if(coming_text.length() == 16){
          String fl=coming_text.substring(0,4);
          int fl_ = fl.toInt();
          String fr=coming_text.substring(4,8);
          int fr_ =fr.toInt();
          String bl=coming_text.substring(8,12);
          int bl_ =bl.toInt();
          String br=coming_text.substring(12,16);
          int br_=br.toInt();
          if(fl_ >=1000 && fr_  >=1000 && bl_ >= 1000 && br_ >= 1000){
            real_fl=fl_;
            real_fr=fr_;
            real_bl=bl_;
            real_br=br_;
            }
          
          
        }
        
  }
  
  //Serial.print("1001201150149874.");
  String a=String(yaw)+String(pitch)+String(roll)+String(throttle)+ String(9999) + ".";
  Serial.print(a);
  delay(2);
  if(yaw==9999){
    yaw=1000;pitch=1000;roll=1000;throttle=1000;
  }else{
   yaw++;pitch++;roll++;throttle++; 
  }
  
 }  
