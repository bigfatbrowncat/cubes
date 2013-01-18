/*
 * AnimatedPopupText.cpp
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#include "AnimatedPopupLine.h"

namespace sfmlcubes
{
	namespace controllers
	{
		AnimatedPopupLine::AnimatedPopupLine(string text, int value, ResourceType type, AnimationType animationType) :
				text(text), value(value), type(type), animationType(animationType), message(NULL)
		{
		}


		AnimatedPopupLine::~AnimatedPopupLine()
		{

		}
	}
}
