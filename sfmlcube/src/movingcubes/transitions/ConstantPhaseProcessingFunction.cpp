/*
 * LinearPhaseProcessingFunction.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include "ConstantPhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			double ConstantPhaseProcessingFunction::process(double linearPhase) const
			{
				return 1;
			}
		}
	}
}
