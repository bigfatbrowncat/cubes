/*
 * LinearPhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef ABSCOSINEPHASEPROCESSINGFUNCTION_H_
#define ABSCOSINEPHASEPROCESSINGFUNCTION_H_

#include "PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class AbsCosinePhaseProcessingFunction : public PhaseProcessingFunction
			{
			private:
				int halfPeriods;
			public:
				AbsCosinePhaseProcessingFunction();
				virtual double process(double linearPhase) const;
				virtual Cloneable* clone() const
				{
					return new AbsCosinePhaseProcessingFunction(*this);
				}
			};
		}
	}
}
#endif
