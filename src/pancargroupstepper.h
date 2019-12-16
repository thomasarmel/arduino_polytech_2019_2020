#ifndef PANCARGROUPSTEPPER_H_INCLUDED
#define PANCARGROUPSTEPPER_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "pancarstepper.h"

#define MAX_STEPPERS 10

namespace pancar
{
    class GroupStepper
    {
    public:
        GroupStepper();
        ~GroupStepper();
        bool push(Stepper &stepper);
        void moveTogetherSameSpeed(unsigned long long nbSteps);

        unsigned short getNbSteppers() const;
        Stepper &get(unsigned short id);

    protected:
        Stepper m_listSteppers[MAX_STEPPERS];
        unsigned short m_nbSteppers;
    };
}

#endif // PANCARGROUPSTEPPER_H_INCLUDED
