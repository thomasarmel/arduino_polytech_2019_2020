#ifndef PANCARSTEPPER_H_INCLUDED
#define PANCARSTEPPER_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar
{
    class Stepper
    {
    public:
        Stepper();
        Stepper(byte dirPin, byte stepPin);
        ~Stepper();
        void setDirection(bool forward);
        void setSpeedDelayMicroseconds(unsigned int delayMicroseconds);
        void move(unsigned long long nbSteps);
        void moveOneStep();

        bool getDirectionForward() const;
        unsigned int getSpeedDelayMicroseconds() const;
        byte getDirPin() const;
        byte getStepPin() const;
        bool getStateLastStep();

    protected:
        byte m_dirPin;
        byte m_stepPin;
        bool m_directionForward;
        unsigned int m_delayMicroseconds;
        bool m_stateLastStep;
    };
}

#endif // PANCARSTEPPER_H_INCLUDED
