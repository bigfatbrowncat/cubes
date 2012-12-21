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
		AnimatedPopupText::AnimatedPopupText(string text, int value, Type type, AnimationType animationType, const Shape& shape) :
				text(text), value(value), type(type), animationType(animationType), shape(shape)
		{
		}


		AnimatedPopupText::~AnimatedPopupText()
		{

		}
	}
}
