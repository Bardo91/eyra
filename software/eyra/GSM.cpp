//
//
//
//
//

#include "GSM.h"
#include <Arduino.h>

namespace eyra{
  GSM::GSM(uint8_t _rxArd, uint8_t _txArd): serial_(_rxArd, _txArd){
    // Init serial port
    serial_.begin(9600);
    delay(1000);

    // Init SIM800L
    serial_.println("AT"); //Once the handshake test is successful, it will back to OK
    printString(pollResponse());
    delay(2000);

  }
  
  bool GSM::unlockSIM(const String &_pin){
    serial_.println("AT+CPIN="+_pin); // Configuring PIN
    printString(pollResponse());
    delay(2000);
  }

  
  bool GSM::init(){
    serial_.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
    printString(pollResponse());
    serial_.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
    printString(pollResponse());
    serial_.println("AT+CREG?"); //Check whether it has registered in the network
    printString(pollResponse());
    serial_.println("AT+CBC"); //Check whether it has registered in the network
    printString(pollResponse());
    serial_.println("AT+CBAND?");
    printString(pollResponse());
    serial_.println("AT+COPS?");
    printString(pollResponse());
    delay(1000);
    
  }
  
  bool GSM::isConnected(){
    
  }
  
  bool GSM::setIpProvider(const String &_server){
    serial_.println("AT+CSTT=\""+_server+"\",\"\",\"\"");
    printString(pollResponse());

    serial_.println("AT+CIICR");
    printString(pollResponse());
    
    serial_.println("AT+CIFSR");
    currentIp_ = pollResponse();
    printString(currentIp_);
    
  }


  bool GSM::sendCustomMessage(const String &_msg){
    serial_.println(_msg);
    printString(pollResponse());
  }
  
  String GSM::pollResponse(int _delay){
    delay(_delay);
    String response;
    while (serial_.available()) {
      char byte = serial_.read();
      response += byte;
    }
    return response;
  }

  void GSM::printString(const String &_str){
    for(int i=0; i<_str.length(); i++) {
      Serial.print(_str.charAt(i));
    }
  }

  String GSM::getRequest(const String &_web, const String &_port, const String &_request){
    serial_.println("AT+CIPSTART=\"TCP\",\"exploreembedded.com\","+_port);
    printString(pollResponse(1000));
    serial_.println("AT+CIPSEND="+String(_request.length()));
    printString(pollResponse(1000));
    serial_.println(_request);
    printString(pollResponse(1000));
  }


}
