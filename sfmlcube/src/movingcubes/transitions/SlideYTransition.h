/*
 * SlideTransition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SLIDEYTRANSITION_H_
#define SLIDEYTRANSITION_H_

#include "Transition.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class SlideYTransition : public Transition
			{
			private:
				float sourceY;
			protected:
				virtual void updateObjects();
			public:
				SlideYTransition(Shape& group);
				virtual ~SlideYTransition();

				void setSourceY(float value)
				{
					if (isInProgress()) throw TRANSITION_IS_IN_PROGRESS_EXCEPTION;
					sourceY = value;
				}
			};
		}
	}
}
#endif
