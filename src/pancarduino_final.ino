#include <pancarwifi.h>
#include <pancargroupstepper.h>
#include <pancarvector.h>
#include <pancarministepper.h>

using namespace pancar;

pancar::Wifi wifi(8, 9);
pancar::Stepper stepperJaune(2, 3);
pancar::Stepper stepperBleu(4, 5);
pancar::Stepper stepperVert(6, 7);
pancar::MiniStepper miniStepper(10, 11, 12, 13);
pancar::GroupStepper groupStepperX;
unsigned int position[2]={0, 0};

void setup() {
  Serial.begin(9600);
  wifi.setSSID("pancarduino");
  wifi.setChannel(11);
  wifi.setNeedListenAtServer(true);
  wifi.setServerPort(8122);
  wifi.initSoftwareSerial();
  wifi.flushSettings();
  
  stepperJaune.setSpeedDelayMicroseconds(4000);
  stepperVert.setSpeedDelayMicroseconds(4000);
  stepperBleu.setSpeedDelayMicroseconds(4000);
  stepperJaune.setDirection(true);
  stepperBleu.setDirection(false);
  groupStepperX.push(stepperJaune);
  groupStepperX.push(stepperBleu);
  stepperVert.setDirection(false);
  miniStepper.setSpeedDelayMilliseconds(3);
}

void loop() {
  pancar::Vector<pancar::Point> pointsArray;
  pointsArray.setDestructorNeedsToDeletePointersToElements(true);
  bool continuerARecevoirPoints=true;
  byte nbTentativesPoints=0;
  while(continuerARecevoirPoints) {
    bool resultRecv=wifi.listenForPoints(pointsArray, 1000);
    if(resultRecv || nbTentativesPoints>=5) {
      continuerARecevoirPoints=false;
    }
    if(pointsArray.size()==0) {
      continuerARecevoirPoints=true;
    } else {
      nbTentativesPoints++;
    }
  }
  Serial.println("ok");
  for(unsigned short i=1; i<pointsArray.size()-1; i+=3) {
    pancar::Point p=pointsArray[i];
    if(p.getX()==0 || p.getY() ==0) {
      pointsArray.remove(i);
      continue;
    }
    Serial.println("Point: "+String(p.getX())+" "+String(p.getY()));
    if(p.getX()-position[0] > 0) {
        stepperJaune.setDirection(true);
        stepperBleu.setDirection(false);
    } else {
        stepperJaune.setDirection(false);
        stepperBleu.setDirection(true);
    }

    if(p.getY()-position[1] > 0) {
        stepperVert.setDirection(false);
    } else {
        stepperVert.setDirection(true);
    }
    groupStepperX.moveTogetherSameSpeed(abs((p.getX()-position[0])/2));
    stepperVert.move(abs((p.getY()-position[1])/2));
    miniStepper.move(100);
    position[0]=p.getX();
    position[1]=p.getY();
  }

}
