/*
 * Transition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <sstream>
#include <cmath>

#include "Transition.h"
#include "Logger.h"

using namespace std;

namespace sfmlcubes
{

	Transition::Transition(CubesGroup& group) :
			group(&group),
			phase(0)
	{
	}

	float Transition::getProcessedPhase() const
	{
		float slope = 1.2;

		switch (function)
		{
		case rfLinear:
			return phase;
		case rfParabolic:
			return phase * phase;
		case rfArctangent:
			return atan(slope * (phase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;
		default:
			Logger::DEFAULT.logError("Strange case in RotateTransition::updateObjects");
			return 0;
		}
	}

	void Transition::setPhase(float value)
	{
		phase = value;
		updateObjects();
	}

	Transition::AdvanceStepResult Transition::advanceStep(double delta)
	{
		if (phase >= 1)
		{
			return asrFinished;
		}
		Transition::AdvanceStepResult res = asrAdvanced;
		phase += delta;
		if (phase > 1)
		{
			phase = 1;
			res = asrFinished;
		}
		updateObjects();
		return res;
	}


	Transition::~Transition()
	{
		// TODO Auto-generated destructor stub
	}

}
