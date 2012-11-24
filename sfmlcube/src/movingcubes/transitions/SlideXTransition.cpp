/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideXTransition.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			SlideXTransition::SlideXTransition() :
					Transition(), sourceX(0)
			{
			}

			SlideXTransition::SlideXTransition(float longitude, PhaseProcessingFunction function, float sourceX) :
					Transition(longitude, function), sourceX(sourceX)
			{
			}

			float SlideXTransition::getValue()
			{
				return (1 - getProcessedPhase()) * sourceX;
			}

			SlideXTransition::~SlideXTransition()
			{
			}
		}
	}
}
