#ifndef PANCARPOINT_H_INCLUDED
#define PANCARPOINT_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar
{
    class Point
    {
    public:
        Point();
        Point(unsigned short x, unsigned short y);
        ~Point();

        unsigned short getX() const;
        unsigned short getY() const;

        void setX(unsigned short x);
        void setY(unsigned short y);

    protected:
        short m_x;
        short m_y;
    };
}

#endif // PANCARPOINT_H_INCLUDED
