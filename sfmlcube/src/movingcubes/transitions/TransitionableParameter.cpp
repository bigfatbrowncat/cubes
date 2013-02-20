/*
 * TransitionableValue.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#include "TransitionableParameter.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			TransitionableParameter::TransitionableParameter(double duration,
			                                                 const PhaseProcessingFunction& function,
			                                                 double startingValue,
			                                                 double endingValue) :
					linearPhase(0.0),
					function((PhaseProcessingFunction*)(function.clone())),
					processedPhase(this->function->process(linearPhase)),
					duration(duration),
					startingValue(startingValue),
					endingValue(endingValue),
					time(0.0),
					value(startingValue)
			{
			}

			TransitionableParameter::TransitionableParameter(const TransitionableParameter& other) :
			        linearPhase(other.linearPhase),
			        function((PhaseProcessingFunction*)(other.function->clone())),
			        processedPhase(other.processedPhase),
			        duration(other.duration),
			        startingValue(other.startingValue),
			        endingValue(other.endingValue),
			        time(other.time),
			        value(other.value)
			{
			}

			void TransitionableParameter::advanceStep(double delta)
			{
				time += delta;
				linearPhase = time / duration;

				if (linearPhase >= 1)
				{
					linearPhase = 1;
					processedPhase = 1;
					value = endingValue;
				}
				else
				{
					processedPhase = function->process(linearPhase);
					value = endingValue * processedPhase + startingValue * (1.0 - processedPhase);
				}
			}

			TransitionableParameter::~TransitionableParameter()
			{
				delete function;
			}
		}
	}
}
