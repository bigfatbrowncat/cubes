/*
 * LinearPhaseProcessingFunction.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef ARCTANGENTPHASEPROCESSINGFUNCTION_H_
#define ARCTANGENTPHASEPROCESSINGFUNCTION_H_

#include "PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class ArctangentPhaseProcessingFunction : public PhaseProcessingFunction
			{
			private:
				double slope;
			public:
				ArctangentPhaseProcessingFunction();
				virtual double process(double linearPhase) const;
				virtual Cloneable* clone() const
				{
					return new ArctangentPhaseProcessingFunction(*this);
				}
			};
		}
	}
}
#endif
