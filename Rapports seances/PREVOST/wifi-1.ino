#include <SoftwareSerial.h>
#include <pancarvector.h>

SoftwareSerial ESP8266(10, 11);

pancar::Vector<String> listenForPoints();

void setup() {
  Serial.begin(9600);
  ESP8266.begin(115200);
  ESP8266.write("AT+CWMODE=2\r\n");
  ESP8266.write("AT+CIPMUX=1\r\n");
  ESP8266.write("AT+CIPSERVER=1,8122\r\n");
}

void loop() {
  pancar::Vector<String> listePoints=listenForPoints();
  for(unsigned short i=0; i<listePoints.size(); i++) {
    Serial.println(listePoints[i]);
  }
}

pancar::Vector<String> listenForPoints() {
  bool writingLine=false;
  String point;
  pancar::Vector<String> listePoints;
  while(1) {
    if(ESP8266.available()) {
      if(writingLine) {
        char car=ESP8266.read();
        Serial.print(car);
        point+=car;
        if((int)car==10) { // "\n"
          writingLine=false;
          if(point[0]=='d'/* && point[1]=='o' && point[2]=='n' && point[3]=='e'*/) {
            return listePoints;
          }
          listePoints.addValue(point);
          point="";
        }
      } else {
        if(ESP8266.find("point:")) {
          Serial.write("CONNECT");
          writingLine=true;
        }
      }
    }
  }
}
