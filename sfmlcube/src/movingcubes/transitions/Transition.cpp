/*
 * Transition.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <sstream>
#include <cmath>

#include "Transition.h"
#include "../../Logger.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			Transition::Transition(Shape& shape, float longitude, PhaseProcessingFunction function) :
					shape(&shape),
					inProgress(false),
					phase(0),
					longitude(longitude),
					function(function)
			{
			}

			Transition::Transition(Shape& shape) :
					shape(&shape),
					inProgress(false),
					phase(0),
					longitude(1),
					function(ppfLinear)
			{
			}

			float Transition::getProcessedPhase() const
			{
				float slope = 1.2;

				switch (function)
				{
				case ppfLinear:
					return phase;
				case ppfParabolic:
					return phase * phase;
				case ppfArctangent:
					return atan(slope * (phase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;
				default:
					Logger::DEFAULT.logError("Strange case in RotateTransition::updateObjects");
					return 0;
				}
			}

			void Transition::advanceStep(double delta)
			{
				inProgress = true;
				if (phase >= 1)
				{
					// Finished
					inProgress = false;
				}
				else
				{
					phase += delta / longitude;
					if (phase > 1)
					{
						phase = 1;
						inProgress = false;
					}
				}
				updateObjects();
			}


			Transition::~Transition()
			{
			}
		}
	}
}
