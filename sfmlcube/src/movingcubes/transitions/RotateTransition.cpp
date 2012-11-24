/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "RotateTransition.h"
#include "../Cube.h"
#include "../Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			RotateTransition::RotateTransition(Shape& shape, float longitude, PhaseProcessingFunction function, float sourceAngle) :
					Transition(shape, longitude, function), sourceAngle(sourceAngle)
			{
				updateObjects();
			}

			RotateTransition::RotateTransition(Shape& shape) :
					Transition(shape), sourceAngle(0)
			{
				updateObjects();
			}

			void RotateTransition::updateObjects()
			{
				getShape().rotatingAngle = (1 - getProcessedPhase()) * sourceAngle;
			}

			RotateTransition::~RotateTransition()
			{
			}
		}
	}
}
