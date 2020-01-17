#include "pancarwifi.h"

using namespace pancar;

Wifi::Wifi() : m_RXPin(10), m_TXPin(11)
{
}

Wifi::Wifi(byte RXPin, byte TXPin)
{
    m_RXPin=RXPin;
    m_TXPin=TXPin;
}

Wifi::~Wifi()
{
    delete m_ESP8266;
}

void Wifi::initSoftwareSerial()
{
    m_ESP8266=new SoftwareSerial(m_RXPin, m_TXPin);
    m_ESP8266->begin(115200);
    delay(1000);
    m_ESP8266->write("AT+CWMODE=2\r\n");
}

byte Wifi::getRXPin() const#include "pancarwifi.h"

using namespace pancar;

Wifi::Wifi() : m_RXPin(10), m_TXPin(11)
{
}

Wifi::Wifi(byte RXPin, byte TXPin)
{
    m_RXPin=RXPin;
    m_TXPin=TXPin;
}

Wifi::~Wifi()
{
    delete m_ESP8266;
}

void Wifi::initSoftwareSerial()
{
    m_ESP8266=new SoftwareSerial(m_RXPin, m_TXPin);
    m_ESP8266->setTimeout(1000);
    m_ESP8266->begin(115200);
    delay(1000);
    m_ESP8266->write("AT+CWMODE=2\r\n");
}

byte Wifi::getRXPin() const
{
    return m_RXPin;
}

byte Wifi::getTXPin() const
{
    return m_TXPin;
}

String Wifi::getSSID() const
{
    return m_SSID;
}

byte Wifi::getChannel() const
{
    return m_channel;
}

bool Wifi::getNeedListenAtServer() const
{
    return m_needListen;
}

unsigned short Wifi::getServerPort() const
{
    return m_serverPort;
}

void Wifi::setRXPin(byte RXPin)
{
    m_RXPin=RXPin;
}

void Wifi::setTXPin(byte TXPin)
{
    m_TXPin=TXPin;
}

void Wifi::setSSID(String SSID)
{
    m_SSID=SSID;
}

void Wifi::setChannel(byte channel)
{
    m_channel=channel;
}

void Wifi::setNeedListenAtServer(bool needListen)
{
    m_needListen=needListen;
}

void Wifi::setServerPort(unsigned short serverPort)
{
    m_serverPort=serverPort;
}

void Wifi::flushSettings()
{
    delay(50);
    m_ESP8266->write(("AT+CWSAP=\""+m_SSID+"\",\"\","+String(m_channel)+",0\r\n").c_str());
    if(m_needListen)
    {
        delay(50);
        m_ESP8266->write("AT+CIPMUX=1\r\n");
        delay(50);
        m_ESP8266->write(("AT+CIPSERVER=1,"+String(m_serverPort)+"\r\n").c_str());
    }
}

bool Wifi::listenForPoints(Vector<Point> &listPoints, unsigned long delayMaxMillis)
{
    bool infiniteLoop=(delayMaxMillis==0);
    unsigned long timeToStopLoop=millis()+delayMaxMillis;
    bool writingLine=false;
    String pointStr;
    pancar::Vector<String> listePoints;
    char carRcv;
    while(infiniteLoop || (millis()<timeToStopLoop))
    {
        if(m_ESP8266->available())
        {
            if(writingLine)
            {
                carRcv=m_ESP8266->read();
                pointStr+=carRcv;
                if((int)carRcv==10) // "\n"
                {
                    writingLine=false;
                    if(pointStr[0]=='d' && pointStr[1]=='o' && pointStr[2]=='n' && pointStr[3]=='e')
                    {
                        return true;
                    }
                    listPoints.addValue(stringToPoint(pointStr));
                    pointStr="";
                }
            }
            else
            {
                if(m_ESP8266->find("point:"))
                {
                    writingLine=true;
                }
            }
        }
    }
    return false;
}

Point Wifi::stringToPoint(String str)
{
    String x_str;
    String y_str;
    bool y=false;
    for(byte j=0; j<str.length(); j++)
    {
        if(isDigit(str.charAt(j)))
        {
            if(y)
            {
                y_str+=str.charAt(j);
            }
            else
            {
                x_str+=str.charAt(j);
            }
            continue;
        }
        if(str.charAt(j) ==',') {
            y=true;
            continue;
        }
    }
    Point retour(x_str.toInt(), y_str.toInt());
    return retour;
}
{
    return m_RXPin;
}

byte Wifi::getTXPin() const
{
    return m_TXPin;
}

String Wifi::getSSID() const
{
    return m_SSID;
}

byte Wifi::getChannel() const
{
    return m_channel;
}

bool Wifi::getNeedListenAtServer() const
{
    return m_needListen;
}

unsigned short Wifi::getServerPort() const
{
    return m_serverPort;
}

void Wifi::setRXPin(byte RXPin)
{
    m_RXPin=RXPin;
}

void Wifi::setTXPin(byte TXPin)
{
    m_TXPin=TXPin;
}

void Wifi::setSSID(String SSID)
{
    m_SSID=SSID;
}

void Wifi::setChannel(byte channel)
{
    m_channel=channel;
}

void Wifi::setNeedListenAtServer(bool needListen)
{
    m_needListen=needListen;
}

void Wifi::setServerPort(unsigned short serverPort)
{
    m_serverPort=serverPort;
}

void Wifi::flushSettings()
{
    delay(50);
    m_ESP8266->write(("AT+CWSAP=\""+m_SSID+"\",\"\","+String(m_channel)+",0\r\n").c_str());
    if(m_needListen)
    {
        delay(50);
        m_ESP8266->write("AT+CIPMUX=1\r\n");
        delay(50);
        m_ESP8266->write(("AT+CIPSERVER=1,"+String(m_serverPort)+"\r\n").c_str());
    }
}

bool Wifi::listenForPoints(Vector<Point> &listPoints, unsigned long delayMaxMillis)
{
    bool infiniteLoop=(delayMaxMillis==0);
    unsigned long timeToStopLoop=millis()+delayMaxMillis;
    bool writingLine=false;
    String pointStr;
    char carRcv;
    while(infiniteLoop || (millis()<timeToStopLoop))
    {
        if(m_ESP8266->available())
        {
            if(writingLine)
            {
                carRcv=m_ESP8266->read();
                pointStr+=carRcv;
                if((int)carRcv==10) // "\n"
                {
                    writingLine=false;
                    if(pointStr[0]=='d' && pointStr[1]=='o' && pointStr[2]=='n' && pointStr[3]=='e')
                    {
                        return true;
                    }
                    listPoints.addValue(stringToPoint(pointStr));
                    pointStr="";
                }
            }
            else
            {
                if(m_ESP8266->find("point:"))
                {
                    writingLine=true;
                }
            }
        }
    }
    return false;
}

Point Wifi::stringToPoint(String str)
{
    String x_str;
    String y_str;
    bool y=false;
    for(byte j=0; j<str.length(); j++)
    {
        if(isDigit(str.charAt(j)))
        {
            if(y)
            {
                y_str+=str.charAt(j);
            }
            else
            {
                x_str+=str.charAt(j);
            }
            continue;
        }
        if(str.charAt(j) ==',') {
            y=true;
            continue;
        }
    }
    Point retour(x_str.toInt(), y_str.toInt());
    return retour;
}
