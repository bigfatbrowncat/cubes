/*
 * TransitionableValue.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef TRANSITIONABLEVALUE_H_
#define TRANSITIONABLEVALUE_H_

#include "PhaseProcessingFunction.h"
#include "../Parameter.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class TransitionableParameter : public Parameter
			{
			private:
				// The current phase, which hasn't been modified with
				// the processing function (0..1)
				double linearPhase;

				// The used phase processing function
				PhaseProcessingFunction* function;

				// The current phase which is modified with the processing function (0..1)
				double processedPhase;

				// The amount of time which shall pass from the phase = 0 to phase = 1
				double duration;

				// The value at t = 0 (or phase = 0)
				double startingValue;

				// The value at t >= duration (or phase >= 1)
				double endingValue;

				// The current time. It could have any positive value. If it's greater or equal to 1, linearPhase shall be 1.
				double time;

				// The current value (the value at the current time)
				double value;

			protected:

				// Advances the time by delta
				virtual void processTimeStep(double delta);

			public:
				TransitionableParameter(TimingManager& timingManager, double duration, const PhaseProcessingFunction& function, double startingValue, double endingValue);
				TransitionableParameter(const TransitionableParameter& other);

				// Returns the current value
				virtual double getValue() const { return value; }

				// This function should tell if the parameter is changing now,
				// or its changes are already ended
				virtual bool isChanging() const { return time < duration; }

				virtual Cloneable* clone() const
				{
					return new TransitionableParameter(*this);
				}

				virtual ~TransitionableParameter();
			};
		}
	}
}
#endif
