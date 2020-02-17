#include "pancarministepper.h"

using namespace pancar;

MiniStepper::MiniStepper()
{
    m_directionForward=true;
    m_delayMilliseconds=5;
    m_in[0]=8;
    m_in[1]=9;
    m_in[2]=10;
    m_in[3]=11;
    pinMode(m_in[0], OUTPUT);
    pinMode(m_in[1], OUTPUT);
    pinMode(m_in[2], OUTPUT);
    pinMode(m_in[3], OUTPUT);
}

MiniStepper::MiniStepper(byte in1, byte in2, byte in3, byte in4)
{
    m_directionForward=true;
    m_delayMilliseconds=5;
    m_in[0]=in1;
    m_in[1]=in2;
    m_in[2]=in3;
    m_in[3]=in4;
    pinMode(m_in[0], OUTPUT);
    pinMode(m_in[1], OUTPUT);
    pinMode(m_in[2], OUTPUT);
    pinMode(m_in[3], OUTPUT);
}

MiniStepper::~MiniStepper()
{
    pinMode(m_in[0], INPUT);
    pinMode(m_in[1], INPUT);
    pinMode(m_in[2], INPUT);
    pinMode(m_in[3], INPUT);
}

void MiniStepper::setDirection(bool forward)
{
    m_directionForward=forward;
}

void MiniStepper::setSpeedDelayMilliseconds(unsigned int delayMilliseconds)
{
    m_delayMilliseconds=delayMilliseconds;
}

void MiniStepper::move(unsigned long long nbSteps)
{
    byte stateMotor=0;
    byte j;
    for(unsigned long long i=0; i<nbSteps; i++)
    {
        if(stateMotor==4)
        {
            stateMotor=0;
        }
        for(j=0; j<4; j++)
        {
            if(m_directionForward)
            {
                digitalWrite(m_in[j], (j==stateMotor));
            }
            else
            {
                digitalWrite(m_in[3-j], (j==stateMotor));
            }
        }
        delay(m_delayMilliseconds);
        stateMotor++;
    }
}

bool MiniStepper::getDirectionForward() const
{
    return m_directionForward;
}

unsigned int MiniStepper::getSpeedDelayMilliseconds() const
{
    return m_delayMilliseconds;
}

byte *MiniStepper::getIns() const
{
    return m_in;
}
