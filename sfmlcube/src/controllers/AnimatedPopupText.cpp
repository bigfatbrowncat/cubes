/*
 * AnimatedPopupText.cpp
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#include "AnimatedPopupText.h"

namespace sfmlcubes
{
	namespace controllers
	{
		AnimatedPopupText::AnimatedPopupText(string text, int value, Type type, const Shape& shape) :
				text(text), value(value), type(type), shape(shape)
		{
		}


		AnimatedPopupText::~AnimatedPopupText()
		{

		}
	}
}
