/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideYTransition.h"
#include "Cube.h"
#include "CubesGroup.h"

using namespace std;

namespace sfmlcubes
{
	SlideYTransition::SlideYTransition(CubesGroup& group) :
			Transition(group),
			sourceY(0)
	{
	}

	void SlideYTransition::updateObjects()
	{
		for (list<Cube>::iterator iter = getGroup().getCubes().begin();
		     iter != getGroup().getCubes().end();
		     iter ++)
		{
			(*iter).slidingY = (1-getProcessedPhase()) * sourceY;
		}
	}

	SlideYTransition::~SlideYTransition()
	{
	}
}
