#ifndef PANCARVECTOR_H_INCLUDED
#define PANCARVECTOR_H_INCLUDED

/**
    NOTE AUX CORRECTEURS:
    J'explique ce code dans un pdf, dossier documents divers
*/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

namespace pancar /// Not really RAM-friendly at this time, must be improved
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
        T &operator[](unsigned int index) const;
        void operator+=(Vector<T> v);
        void operator+=(const T &element);
        bool remove(unsigned int index);

    protected:
        unsigned int m_size;
        void *m_firstElementArray[2];
    };

    template <typename T>
    Vector<T>::Vector() : m_size(0)
    {}

    template <typename T>
    Vector<T>::~Vector()
    {}

    template <typename T>
    unsigned int Vector<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    void Vector<T>::add(const T &element)
    {
        if(m_size==0)
        {
            m_firstElementArray[0]=(void*)&element;
            m_firstElementArray[1]=0;
        }
        else
        {
            void *pointerNext=&m_firstElementArray;
            for(unsigned int i=0; i<(m_size-1); i++)
            {
                pointerNext=(*((void*(*)[2])pointerNext))[1];
            }
            void **elementArray=(void**)malloc(sizeof(void*) * 2);
            elementArray[0]=(void*)&element;
            elementArray[1]=0;
            (*((void*(*)[2])pointerNext))[1]=(void*)elementArray;
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
        void *pointerNext=m_firstElementArray[1];
        for(unsigned int i=0; i<(index-1); i++)
        {
            pointerNext=(*((void*(*)[2])pointerNext))[1];
        }
        return *((T*)(*((void*(*)[2])pointerNext))[0]);
    }

    template<typename T>
    T &Vector<T>::operator[](unsigned int index) const
    {
        return get(index);
    }

    template<typename T>
    void Vector<T>::operator+=(Vector<T> v)
    {
        for(unsigned int i=0; i<v.size(); i++)
        {
            add(v.get(i));
        }
    }

    template<typename T>
    void Vector<T>::operator+=(const T &element)
    {
        add(element);
    }

    template<typename T>
    bool Vector<T>::remove(unsigned int index)
    {
        if(m_size<=index)
        {
            return false;
        }
        if(index==0)
        {
            m_firstElementArray[0]=(*((void*(*)[2])m_firstElementArray[1]))[0];
            m_firstElementArray[1]=(*((void*(*)[2])m_firstElementArray[1]))[1];
        }
        else
        {
            void *pointerNext=&m_firstElementArray;
            for(unsigned int i=0; i<(index-1); i++)
            {
                pointerNext=(*((void*(*)[2])pointerNext))[1];
            }
            (*((void*(*)[2])pointerNext))[1]=(*((void*(*)[2]) (*((void*(*)[2])pointerNext))[1] ))[1];
        }
        m_size--;
        return true;
    }

    template<typename T>
    Vector<T> operator+(Vector<T> const& a, Vector<T> const& b)
    {
        Vector<T> v;
        for(unsigned int i=0; i<a.size(); i++)
        {
            v.add(a.get(i));
        }
        for(unsigned int i=0; i<b.size(); i++)
        {
            v.add(b.get(i));
        }
        return v;
    }
}

#endif // PANCARVECTOR_H_INCLUDED
