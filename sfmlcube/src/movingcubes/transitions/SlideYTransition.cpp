/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideYTransition.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			SlideYTransition::SlideYTransition(float longitude, PhaseProcessingFunction function, float sourceY) :
					Transition(longitude, function),	sourceY(sourceY)
			{
			}

			SlideYTransition::SlideYTransition() :
					Transition(), sourceY(0)
			{
			}

			float SlideYTransition::getValue()
			{
				return (1 - getProcessedPhase()) * sourceY;
			}

			SlideYTransition::~SlideYTransition()
			{
			}
		}
	}
}
