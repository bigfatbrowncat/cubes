/*
 * TimedController.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "TimingManager.h"
#include "TimedController.h"

namespace sfmlcubes
{
	TimedController::TimedController(TimingManager& timingManager) : timingManager(timingManager)
	{
		timingManager.add(*this);
	}
	TimedController::~TimedController()
	{
		timingManager.remove(*this);
	}

}
