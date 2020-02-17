#ifndef PANCARMINISTEPPER_H_INCLUDED
#define PANCARMINISTEPPER_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar
{
    class MiniStepper
    {
    public:
        MiniStepper();
        MiniStepper(byte in1, byte in2, byte in3, byte in4);
        ~MiniStepper();
        void setIns(byte in1, byte in2, byte in3, byte in4);
        void setDirection(bool forward);
        void setSpeedDelayMilliseconds(unsigned int delayMilliseconds);
        void move(unsigned long long nbSteps);

        bool getDirectionForward() const;
        unsigned int getSpeedDelayMilliseconds() const;
        byte *getIns() const;

    protected:
        byte m_in[4];
        bool m_directionForward;
        unsigned int m_delayMilliseconds;
    };
}

#endif // PANCARMINISTEPPER_H_INCLUDED
