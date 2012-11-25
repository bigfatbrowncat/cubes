/*
 * Transition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#define TRANSITION_IS_IN_PROGRESS_EXCEPTION			12301

#include <list>

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class Transition
			{
			public:
				enum PhaseProcessingFunction
				{
					ppfConstant,
					ppfLinear,
					ppfArctangent,
					ppfParabolic,
					ppfAbsSine
				};

			private:
				bool inProgress;
				float phase;
				float longitude;
				PhaseProcessingFunction function;
				float sourceValue;
			protected:
				float getProcessedPhase() const;
			public:
				Transition(float longitude, PhaseProcessingFunction function, float sourceValue);
				Transition();

				void advanceStep(double delta);
				virtual ~Transition();

				float getPhase() const { return phase; }
				bool isInProgress() const { return inProgress; }

				virtual float getValue();
			};
		}
	}
}

#endif
