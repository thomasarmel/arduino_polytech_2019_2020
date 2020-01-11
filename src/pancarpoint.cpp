#include "pancarpoint.h"

using namespace pancar;

Point::Point() : m_x(0), m_y(0)
{}

Point::Point(unsigned short x, unsigned short y) : m_x(x), m_y(y)
{}

Point::~Point()
{}

void Point::setX(unsigned short x) 
{
	m_x=x;
}

void Point::setY(unsigned short y) 
{
	m_y=y;
}

unsigned short Point::getX() const
{ 
	return m_x ; 
}

unsigned short Point::getY() const
{ 
	return m_y;
}
