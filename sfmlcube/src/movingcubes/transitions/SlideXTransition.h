/*
 * SlideTransition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SLIDEXTRANSITION_H_
#define SLIDEXTRANSITION_H_

#include "Transition.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		namespace transitions
		{
			class SlideXTransition : public Transition
			{
			private:
				float sourceX;
			public:
				SlideXTransition(float longitude, PhaseProcessingFunction function, float sourceX);
				SlideXTransition();
				virtual ~SlideXTransition();

				virtual float getValue();
			};
		}
	}
}
#endif
