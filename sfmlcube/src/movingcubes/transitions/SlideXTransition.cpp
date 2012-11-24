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
			SlideXTransition::SlideXTransition(Shape& shape) :
					Transition(shape), sourceX(0)
			{
				updateObjects();
			}

			SlideXTransition::SlideXTransition(Shape& shape, float longitude, PhaseProcessingFunction function, float sourceX) :
					Transition(shape, longitude, function), sourceX(sourceX)
			{
				updateObjects();
			}

			void SlideXTransition::updateObjects()
			{
				getShape().slidingX = (1 - getProcessedPhase()) * sourceX;
			}

			SlideXTransition::~SlideXTransition()
			{
			}
		}
	}
}
