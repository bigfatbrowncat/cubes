/*
 * ConstantParameter.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include "ConstantParameter.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		ConstantParameter::ConstantParameter(TimingManager& timingManager, double value) :
				Parameter(timingManager),
				value(value)
		{

		}

	}
}
