/*
 * LinearPhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef CONSTANTPHASEPROCESSINGFUNCTION_H_
#define CONSTANTPHASEPROCESSINGFUNCTION_H_

#include "PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class ConstantPhaseProcessingFunction : public PhaseProcessingFunction
			{
			public:
				virtual double process(double linearPhase) const;
				virtual Cloneable* clone() const
				{
					return new ConstantPhaseProcessingFunction(*this);
				}
			};
		}
	}
}
#endif
