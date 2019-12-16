#include "pancargroupstepper.h"

using namespace pancar;

GroupStepper::GroupStepper()
{
    m_nbSteppers=0;
}

GroupStepper::~GroupStepper()
{}

bool GroupStepper::push(Stepper &stepper)
{
    if(m_nbSteppers==MAX_STEPPERS)
    {
        return false;
    }
    m_listSteppers[m_nbSteppers]=stepper;
    m_nbSteppers++;
    return true;
}

void GroupStepper::moveTogetherSameSpeed(unsigned long long nbSteps)
{
    if(m_nbSteppers==0)
    {
        return;
    }
    unsigned int delayStepMicroseconds=m_listSteppers[0].getSpeedDelayMicroseconds();
    for(unsigned long long i=0; i<nbSteps; i++)
    {
        for(unsigned short j=0; j<m_nbSteppers; j++)
        {
            m_listSteppers[j].moveOneStep();
        }
        delayMicroseconds(delayStepMicroseconds);
    }
}

unsigned short GroupStepper::getNbSteppers() const
{
    return m_nbSteppers;
}

Stepper &GroupStepper::get(unsigned short id)
{
    return m_listSteppers[id];
}
