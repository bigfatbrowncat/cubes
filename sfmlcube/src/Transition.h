/*
 * Transition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <list>

using namespace std;

namespace sfmlcubes
{
	class CubesGroup;

	class Transition
	{
	public:
		enum AdvanceStepResult
		{
			asrAdvanced,
			asrFinished
		};

		enum PhaseProcessingFunction
		{
			rfLinear,
			rfArctangent,
			rfParabolic
		};


	private:
		CubesGroup* group;
		float phase;
		PhaseProcessingFunction function;
	protected:
		float getProcessedPhase() const;
		CubesGroup& getGroup() { return *group; }
		virtual void updateObjects() = 0;
	public:
		Transition(CubesGroup& group);

		AdvanceStepResult advanceStep(double delta);
		virtual ~Transition();

		void setFunction(PhaseProcessingFunction value) { function = value; }
		void setPhase(float value);

		float getPhase() const { return phase; }
	};

}

#endif
