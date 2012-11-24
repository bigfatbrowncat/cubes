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
			public:
				SlideYTransition(float longitude, PhaseProcessingFunction function, float sourceY);
				SlideYTransition();
				virtual ~SlideYTransition();

				virtual float getValue();
			};
		}
	}
}
#endif
