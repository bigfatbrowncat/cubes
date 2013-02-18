/*
 * LinearPhaseProcessingFunction.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include <math.h>

#include "ParabolicPhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			double ParabolicPhaseProcessingFunction::process(double linearPhase) const
			{
				return linearPhase * linearPhase;
			}
		}
	}
}
