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
				RotateTransition(Shape& group);
				virtual ~RotateTransition();

				void setSourceAngle(float value)
				{
					if (isInProgress()) throw TRANSITION_IS_IN_PROGRESS_EXCEPTION;
					sourceAngle = value;
				}
			};
		}
	}
}
#endif
