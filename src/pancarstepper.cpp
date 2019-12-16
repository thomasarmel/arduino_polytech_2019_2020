#include "pancarstepper.h"

using namespace pancar;

Stepper::Stepper() : m_dirPin(2), m_stepPin(3)
{
    setDirection(true);
    m_delayMicroseconds=500;
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_stepPin, OUTPUT);
}

Stepper::Stepper(byte dirPin, byte stepPin) : m_dirPin(dirPin), m_stepPin(stepPin)
{
    setDirection(true);
    m_delayMicroseconds=500;
    pinMode(m_dirPin, OUTPUT);
    pinMode(m_stepPin, OUTPUT);
}

Stepper::~Stepper()
{
    pinMode(m_dirPin, INPUT);
    pinMode(m_stepPin, INPUT);
}

void Stepper::setDirection(bool forward)
{
    m_directionForward=forward;
    digitalWrite(m_dirPin, m_directionForward);
}

void Stepper::setSpeedDelayMicroseconds(unsigned int delayMicroseconds)
{
    m_delayMicroseconds=delayMicroseconds;
}

void Stepper::move(unsigned long long nbSteps)
{
    for(unsigned long long i=0; i<nbSteps; i++)
    {
        digitalWrite(m_stepPin, HIGH);
        delayMicroseconds(m_delayMicroseconds);
        digitalWrite(m_stepPin, LOW);
        delayMicroseconds(m_delayMicroseconds);
    }
    m_stateLastStep=false;
}

void Stepper::moveOneStep()
{
    m_stateLastStep=!m_stateLastStep;
    digitalWrite(m_stepPin, m_stateLastStep);
}

bool Stepper::getDirectionForward() const
{
    return m_directionForward;
}

unsigned int Stepper::getSpeedDelayMicroseconds() const
{
    return m_delayMicroseconds;
}

byte Stepper::getDirPin() const
{
    return m_dirPin;
}

byte Stepper::getStepPin() const
{
    return m_stepPin;
}

bool Stepper::getStateLastStep()
{
    return m_stateLastStep;
}
