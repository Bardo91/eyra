//
//
//
//
//

#ifndef EYRA_GSM_H_
#define EYRA_GSM_H_

#include <SoftwareSerial.h>

namespace eyra{
  class GSM{
    public:
      /// Instantiate the GSM module wrapper through the a Software Serial 
      /// using given pins
      /// \param _rxArd: RX pin in arduino for the SoftwareSerial
      /// \param _txArd: TX pin in arduino for the SoftwareSerial
      GSM(uint8_t _rxArd, uint8_t _txArd);
  
      /// Unlock SIM card with given pin;
      /// \param _pin: string with pin to unlock card
      /// \return true if unlocked false, if not
      bool unlockSIM(const String &_pin);

      /// Init checks and set ups. Needs to be called after unlocking SIM
      bool init();
  
      /// Check whether the module is properly connected to the network
      bool isConnected();
  
      /// Set the IP server provider
      bool setIpProvider(const String &_server);

      bool sendCustomMessage(const String &_msg);

      String pollResponse(int _delay = 500);

      void printString(const String &_str);

      String getRequest(const String &_web, const String &_port, const String &_request);
      
    private:
      SoftwareSerial serial_;   
      String currentIp_; 
  };
}


#endif
