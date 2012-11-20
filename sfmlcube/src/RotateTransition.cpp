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
			targetAngle(0)
	{
	}

	void RotateTransition::updateObjects()
	{
		for (list<Cube>::iterator iter = getGroup().getCubes().begin();
		     iter != getGroup().getCubes().end();
		     iter ++)
		{
			(*iter).rotatingCenterX = rotatingCenterX;
			(*iter).rotatingCenterY = rotatingCenterY;
			(*iter).rotatingAngle = getProcessedPhase() * targetAngle * 90;
		}
	}

	void RotateTransition::setAngle(int value)
	{
		targetAngle = value;
		updateObjects();
	}

	void RotateTransition::setRotatingCenter(int x, int y, CubeRotatingCenterType crct)
	{
		rotatingCenterX = x;
		rotatingCenterY = y;
		rotatingCenterType = crct;
		updateObjects();
	}

	RotateTransition::~RotateTransition()
	{
	}
}
