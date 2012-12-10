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
		int AnimatedPopupText::lastUId = 0;

		AnimatedPopupText::AnimatedPopupText(string text) :
				text(text), age(0)
		{
			uId = lastUId;
		}


		AnimatedPopupText::~AnimatedPopupText()
		{

		}
	}
}
