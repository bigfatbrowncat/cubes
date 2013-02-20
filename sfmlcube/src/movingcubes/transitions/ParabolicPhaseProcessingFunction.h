/*
 * LinearPhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef PARABOLICPHASEPROCESSINGFUNCTION_H_
#define PARABOLICPHASEPROCESSINGFUNCTION_H_

#include "PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class ParabolicPhaseProcessingFunction : public PhaseProcessingFunction
			{
			public:
				virtual double process(double linearPhase) const;
				virtual Cloneable* clone() const
				{
					return new ParabolicPhaseProcessingFunction(*this);
				}
			};
		}
	}
}
#endif
