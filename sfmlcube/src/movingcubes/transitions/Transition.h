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
		class Shape;

		namespace transitions
		{
			class Transition
			{
				friend class Shape;
			public:
				enum PhaseProcessingFunction
				{
					ppfLinear,
					ppfArctangent,
					ppfParabolic
				};

			private:
				Shape* shape;
				bool inProgress;
				float phase;
				float longitude;
				PhaseProcessingFunction function;
			protected:
				float getProcessedPhase() const;
				Shape& getShape() { return *shape; }
				virtual void updateObjects() {}
			public:
				Transition(Shape& group, float longitude, PhaseProcessingFunction function);
				Transition(Shape& group);

				void advanceStep(double delta);
				virtual ~Transition();

				float getPhase() const { return phase; }
				bool isInProgress() const { return inProgress; }

			};
		}
	}
}

#endif
