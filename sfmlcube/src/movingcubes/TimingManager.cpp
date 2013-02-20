/*
 * TimingManager.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "TimingManager.h"
#include "TimedController.h"

namespace sfmlcubes {

	void TimingManager::add(TimedController& tc)
	{
		controllers.push_back(&tc);
	}
	void TimingManager::remove(TimedController& tc)
	{
		controllers.remove(&tc);
	}

	void TimingManager::processTimeStep(double dt)
	{
		for (list<TimedController*>::iterator iter = controllers.begin(); iter != controllers.end(); iter ++)
		{
			(*iter)->processTimeStep(dt);
		}
	}

}
