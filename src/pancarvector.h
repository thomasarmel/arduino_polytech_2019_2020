#ifndef PANCARVECTOR_H_INCLUDED
#define PANCARVECTOR_H_INCLUDED

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar
{
    template <typename T>
    class Vector
    {
    public:
        Vector();
        ~Vector();
        unsigned int size() const;
        void add(const T &element);
        T &get(unsigned int index) const;

    private:
        unsigned int m_size;
        void *m_firstElementArray[2];
    };

    template<typename T>
    Vector<T>::Vector() : m_size(0)
    {}

    template<typename T>
    Vector<T>::~Vector()
    {}

    template<typename T>
    unsigned int Vector<T>::size() const
    {
        return m_size;
    }

    template<typename T>
    void Vector<T>::add(const T &element)
    {
        if(m_size==0)
        {
            m_firstElementArray[0]=&element;
            m_firstElementArray[1]=0;
        }
        else
        {
            void *pointerNext=&m_firstElementArray;
            for(unsigned int i=0; i<(m_size-1); i++)
            {
                pointerNext=(*((void*(*)[2])pointerNext))[1];
            }
            Serial.println((*((T*)((*((void*(*)[2])pointerNext))[0]))));
            void *elementArray[2]={&element, 0};
            (*((void*(*)[2])pointerNext))[1]=&elementArray;
            void *p=&elementArray;
            Serial.println((int)p);
            Serial.println(*((T*)(*((void*(*)[2])p))[0]));
        }
        m_size++;
    }

    template<typename T>
    T &Vector<T>::get(unsigned int index) const
    {
        if(index==0)
        {
            return *((T*)(m_firstElementArray[0]));
        }
        void *pointerNext=&m_firstElementArray;
        for(unsigned int i=0; i<(m_size-1); i++)
        {
            pointerNext=(*((void*(*)[2])pointerNext))[1];
        }
        void *p=pointerNext;
        Serial.println((int)p);
        Serial.println(*((T*)(*((void*(*)[2])p))[0]));
        return *((T*)(*((void*(*)[2])p))[0]);
    }
}

#endif // PANCARVECTOR_H_INCLUDED
