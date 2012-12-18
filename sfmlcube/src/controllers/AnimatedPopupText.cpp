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
		AnimatedPopupText::AnimatedPopupText(string text, int value, const Shape& shape) :
				text(text), value(value), shape(shape)
		{
		}


		AnimatedPopupText::~AnimatedPopupText()
		{

		}
	}
}
