/*
 * TimingManager.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "TimingManager.h"
#include "TimeDependent.h"

namespace sfmlcubes {

	void TimingManager::add(TimeDependent& tc)
	{
		controllers.push_back(&tc);
	}
	void TimingManager::remove(TimeDependent& tc)
	{
		controllers.remove(&tc);
	}

	void TimingManager::processTimeStep(double dt)
	{
		for (list<TimeDependent*>::iterator iter = controllers.begin(); iter != controllers.end(); iter ++)
		{
			(*iter)->processTimeStep(dt);
		}
	}

}
