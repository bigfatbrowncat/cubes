/*
 * SlideTransition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef ROTATETRANSITION_H_
#define ROTATETRANSITION_H_

#include "Transition.h"
#include "../CubeRotatingCenterType.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{

			class RotateTransition : public Transition
			{
			private:
				int sourceAngle;
			public:
				RotateTransition(float longitude, PhaseProcessingFunction function, float sourceAngle);
				RotateTransition();
				virtual ~RotateTransition();

				virtual float getValue();
			};
		}
	}
}
#endif
