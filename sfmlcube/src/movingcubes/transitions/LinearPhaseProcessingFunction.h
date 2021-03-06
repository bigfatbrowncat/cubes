/*
 * LinearPhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef LINEARPHASEPROCESSINGFUNCTION_H_
#define LINEARPHASEPROCESSINGFUNCTION_H_

#include "PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class LinearPhaseProcessingFunction : public PhaseProcessingFunction
			{
			public:
				virtual double process(double linearPhase) const;
				virtual Cloneable* clone() const
				{
					return new LinearPhaseProcessingFunction(*this);
				}
			};
		}
	}
}
#endif
