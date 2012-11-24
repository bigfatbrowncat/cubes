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
			SlideYTransition::SlideYTransition(Shape& shape, float longitude, PhaseProcessingFunction function, float sourceY) :
					Transition(shape, longitude, function),	sourceY(sourceY)
			{
				updateObjects();
			}

			SlideYTransition::SlideYTransition(Shape& shape) :
					Transition(shape), sourceY(0)
			{
				updateObjects();
			}

			void SlideYTransition::updateObjects()
			{
				getShape().slidingY = (1 - getProcessedPhase()) * sourceY;
			}

			SlideYTransition::~SlideYTransition()
			{
			}
		}
	}
}
