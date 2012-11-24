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
					ppfLinear,
					ppfArctangent,
					ppfParabolic
				};

			private:
				bool inProgress;
				float phase;
				float longitude;
				PhaseProcessingFunction function;
			protected:
				float getProcessedPhase() const;
			public:
				Transition(float longitude, PhaseProcessingFunction function);
				Transition();

				void advanceStep(double delta);
				virtual ~Transition();

				float getPhase() const { return phase; }
				bool isInProgress() const { return inProgress; }

				virtual float getValue() = 0;
			};
		}
	}
}

#endif
