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
			RotateTransition::RotateTransition(Shape& group) :
					Transition(group),
					sourceAngle(0)
			{
			}

			void RotateTransition::updateObjects()
			{
				getGroup().rotatingAngle = (1 - getProcessedPhase()) * sourceAngle;
			}

			RotateTransition::~RotateTransition()
			{
			}
		}
	}
}
