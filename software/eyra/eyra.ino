//
//
//
//

#include "GSM.h"


eyra::GSM *gsm;

void setup() {
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  Serial.println("Initializing...");

  gsm = new eyra::GSM(3,2);

  gsm->unlockSIM("4310");
  gsm->init();
  
  gsm->setIpProvider("ac.vodafone.es");

  //gsm->getRequest("exploreembedded.com", "80", "GET exploreembedded.com/wiki/images/1/15/Hello.txt HTTP/1.0");
}

void loop() {
  if(Serial.available()){
    String msg="";
    while (Serial.available()) {
      char byte = Serial.read();
      msg += byte;  
    }
    gsm->sendCustomMessage(msg);
  }
  
  delay(100);
}
