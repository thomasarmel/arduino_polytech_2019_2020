// SOURCE: https://github.com/McNeight/MemoryFree

#ifndef	PANCARMEMORY_H_INCLUDED
#define PANCARMEMORY_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar
{
    class Memory
    {
    public:
        static int free();

    private:
        static int freeListSize();
    };
}

#endif
