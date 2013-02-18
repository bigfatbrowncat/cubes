/*
 * LinearPhaseProcessingFunction.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include <math.h>

#include "AbsCosinePhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			AbsCosinePhaseProcessingFunction::AbsCosinePhaseProcessingFunction() : halfPeriods(6) {}

			double AbsCosinePhaseProcessingFunction::process(double linearPhase) const
			{
				return fabs(cos(0.5 * halfPeriods * M_PI * linearPhase));
			}
		}
	}
}
