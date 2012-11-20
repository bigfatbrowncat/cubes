/*
 * SlideTransition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <list>

#include "SlideXTransition.h"
#include "Cube.h"
#include "CubesGroup.h"

using namespace std;

namespace sfmlcubes
{
	SlideXTransition::SlideXTransition(CubesGroup& group) :
			Transition(group),
			sourceX(0)
	{
	}

	void SlideXTransition::updateObjects()
	{
		for (list<Cube>::iterator iter = getGroup().getCubes().begin();
		     iter != getGroup().getCubes().end();
		     iter ++)
		{
			(*iter).slidingX = (1-getProcessedPhase()) * sourceX;
		}
	}

	SlideXTransition::~SlideXTransition()
	{
	}
}
