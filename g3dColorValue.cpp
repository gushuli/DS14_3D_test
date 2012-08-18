#include "g3dColorValue.h"


const ColorValue ColorValue::ZERO = ColorValue(0.0,0.0,0.0,0.0);
const ColorValue ColorValue::Black = ColorValue(0.0,0.0,0.0);
const ColorValue ColorValue::White = ColorValue(1.0,1.0,1.0);
const ColorValue ColorValue::Red = ColorValue(1.0,0.0,0.0);
const ColorValue ColorValue::Green = ColorValue(0.0,1.0,0.0);
const ColorValue ColorValue::Blue = ColorValue(0.0,0.0,1.0);

ColorValue::~ColorValue(void)
{
}

bool ColorValue::operator==(const ColorValue& rhs) const
{
	return (r == rhs.r &&
		g == rhs.g &&
		b == rhs.b &&
		a == rhs.a);
}
//---------------------------------------------------------------------
bool ColorValue::operator!=(const ColorValue& rhs) const
{
	return !(*this == rhs);
}
