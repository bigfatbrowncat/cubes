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
			protected:
				virtual void updateObjects();
			public:
				RotateTransition(Shape& shape, float longitude, PhaseProcessingFunction function, float sourceAngle);
				RotateTransition(Shape& shape);
				virtual ~RotateTransition();
			};
		}
	}
}
#endif
