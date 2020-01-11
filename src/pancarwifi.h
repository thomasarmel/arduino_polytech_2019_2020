#ifndef PANCARSTEPPER_H_INCLUDED
#define PANCARSTEPPER_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <SoftwareSerial.h>
#include "pancarvector.h"
#include "pancarpoint.h"

namespace pancar
{
    class Wifi
    {
    public:
        Wifi();
        Wifi(byte RXPin, byte TXPin);
        ~Wifi();

        byte getRXPin() const;
        byte getTXPin() const;
        String getSSID() const;
        byte getChannel() const;
        bool getNeedListen() const;
        unsigned short getServerPort() const;

        void setRXPin(byte RXPin);
        void setTXPin(byte TXPin);
        void setSSID(String SSID);
        void setChannel(byte channel);
        void setNeedListenAtServer(bool needListen);
        void setServerPort(unsigned short serverPort);

        void initSoftwareSerial();
        void flushSettings();
        bool listenForPoints(Vector<Point> &listPoints, unsigned long delayMaxMillis=0);

    protected:
        Point stringToPoint(String str);

        byte m_RXPin;
        byte m_TXPin;
        String m_SSID="pancarduino";
        byte m_channel;
        bool m_needListen=false;
        unsigned short m_serverPort=8122;
        SoftwareSerial *m_ESP8266;
    };
}

#endif // PANCARSTEPPER_H_INCLUDED
