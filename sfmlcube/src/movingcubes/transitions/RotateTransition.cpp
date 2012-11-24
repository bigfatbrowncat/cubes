/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "RotateTransition.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			RotateTransition::RotateTransition(float longitude, PhaseProcessingFunction function, float sourceAngle) :
					Transition(longitude, function), sourceAngle(sourceAngle)
			{
			}

			RotateTransition::RotateTransition() :
					Transition(), sourceAngle(0)
			{
			}

			float RotateTransition::getValue()
			{
				return (1 - getProcessedPhase()) * sourceAngle;
			}

			RotateTransition::~RotateTransition()
			{
			}
		}
	}
}
