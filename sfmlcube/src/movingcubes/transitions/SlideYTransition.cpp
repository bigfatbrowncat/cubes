/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideYTransition.h"
#include "../Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			SlideYTransition::SlideYTransition(Shape& group) :
					Transition(group),
					sourceY(0)
			{
			}

			void SlideYTransition::updateObjects()
			{
				getGroup().slidingY = (1-getProcessedPhase()) * sourceY;
			}

			SlideYTransition::~SlideYTransition()
			{
			}
		}
	}
}
