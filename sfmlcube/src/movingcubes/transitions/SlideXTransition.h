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
			protected:
				virtual void updateObjects();
			public:
				SlideXTransition(Shape& shape, float longitude, PhaseProcessingFunction function, float sourceX);
				SlideXTransition(Shape& shape);
				virtual ~SlideXTransition();
			};
		}
	}
}
#endif
