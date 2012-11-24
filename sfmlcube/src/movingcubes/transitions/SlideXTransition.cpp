/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideXTransition.h"
#include "../Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			SlideXTransition::SlideXTransition(Shape& group) :
					Transition(group),
					sourceX(0)
			{
			}

			void SlideXTransition::updateObjects()
			{
				getGroup().slidingX = (1 - getProcessedPhase()) * sourceX;
			}

			SlideXTransition::~SlideXTransition()
			{
			}
		}
	}
}
