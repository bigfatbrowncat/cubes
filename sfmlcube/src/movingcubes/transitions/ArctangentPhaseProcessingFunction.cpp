/*
 * LinearPhaseProcessingFunction.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include <math.h>

#include "ArctangentPhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			ArctangentPhaseProcessingFunction::ArctangentPhaseProcessingFunction() :
				slope(0.6)
			{

			}

			double ArctangentPhaseProcessingFunction::process(double linearPhase) const
			{
				return atan(slope * (linearPhase - 0.5)*M_PI*2) / (2 * atan(slope * M_PI)) + 0.5;
			}
		}
	}
}
