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
	class CubesGroup;

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
		CubesGroup* group;
		bool inProgress;
		float phase;
		float longitude;
		PhaseProcessingFunction function;
	protected:
		float getProcessedPhase() const;
		CubesGroup& getGroup() { return *group; }
		virtual void updateObjects() = 0;
	public:
		Transition(CubesGroup& group);

		void advanceStep(double deltaT);
		virtual ~Transition();

		void setFunction(PhaseProcessingFunction value)
		{
			if (inProgress) throw TRANSITION_IS_IN_PROGRESS_EXCEPTION;
			function = value;
		}
		void setLongitude(float value)
		{
			if (inProgress) throw TRANSITION_IS_IN_PROGRESS_EXCEPTION;
			longitude = value;
		}

		void reset();

		float getPhase() const { return phase; }
		bool isInProgress() const { return inProgress; }

	};

}

#endif
