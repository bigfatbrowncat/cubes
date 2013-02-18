/*
 * LinearPhaseProcessingFunction.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include "LinearPhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			double LinearPhaseProcessingFunction::process(double linearPhase) const
			{
				return linearPhase;
			}
		}
	}
}
