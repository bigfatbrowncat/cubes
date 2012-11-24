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
				SlideXTransition(Shape& group);
				virtual ~SlideXTransition();

				void setSourceX(float value)
				{
					if (isInProgress()) throw TRANSITION_IS_IN_PROGRESS_EXCEPTION;
					sourceX = value;
				}
			};
		}
	}
}
#endif
