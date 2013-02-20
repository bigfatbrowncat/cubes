/*
 * TimeDependent.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "TimingManager.h"
#include "TimeDependent.h"

namespace sfmlcubes
{
	TimeDependent::TimeDependent(TimingManager& timingManager) : timingManager(timingManager)
	{
		timingManager.add(*this);
	}
	TimeDependent::~TimeDependent()
	{
		timingManager.remove(*this);
	}

}
