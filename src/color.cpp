#include "color.h"

rast::Color::Color (color_t red, color_t green, color_t blue)
{
	m_channels = new color_t[3];
	m_channels[0] = red;
	m_channels[1] = green;
	m_channels[2] = blue;
}

rast::Color& rast::Color::Color::operator=( const Color& other ){
	if (this == &other) return *this;

	delete [] m_channels; //<! Deallocate old storage area.

	//<! Allocate new storage area
	m_channels = new color_t[3];

	//<! Copy content to new container
	for(auto i(0ul); i < 3; ++i)
		m_channels[i] = other.m_channels[i];

	return *this;
}

color_t rast::Color::red() const{
    return m_channels[0];
}

color_t rast::Color::green() const{
    return m_channels[1];
}

color_t rast::Color::blue() const{
    return m_channels[2];
}