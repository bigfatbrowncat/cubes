/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "RotateTransition.h"
#include "Cube.h"
#include "CubesGroup.h"

using namespace std;

namespace sfmlcubes
{
	RotateTransition::RotateTransition(CubesGroup& group) :
			Transition(group),
			sourceAngle(0)
	{
	}

	void RotateTransition::updateObjects()
	{
		/*for (list<Cube>::iterator iter = getGroup().getCubes().begin();
		     iter != getGroup().getCubes().end();
		     iter ++)*/
		{
/*			getGroup().rotatingCenterX = getGroup().getRotatingCenterX();
			getGroup().rotatingCenterY = getGroup().getRotatingCenterY();
			getGroup().rotatingCenterType = getGroup().getRotatingCenterType();*/
			getGroup().rotatingAngle = (1 - getProcessedPhase()) * sourceAngle;
		}
	}

	void RotateTransition::setSourceAngle(int value)
	{
		sourceAngle = value;
		updateObjects();
	}

	RotateTransition::~RotateTransition()
	{
	}
}
