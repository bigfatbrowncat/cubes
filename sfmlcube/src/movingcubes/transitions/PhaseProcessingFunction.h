/*
 * PhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef PHASEPROCESSINGFUNCTION_H_
#define PHASEPROCESSINGFUNCTION_H_

#include "../../Cloneable.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{

			class PhaseProcessingFunction : public Cloneable
			{
			public:
				virtual double process(double linearPhase) const = 0;
			};

		}
	}
}
#endif
