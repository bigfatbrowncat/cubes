/*
 * SlideTransition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SLIDEYTRANSITION_H_
#define SLIDEYTRANSITION_H_

#include "Transition.h"
//#include "CubesGroup.h"

namespace sfmlcubes
{
	class CubesGroup;

	class SlideYTransition : public Transition
	{
	private:
		float sourceY;
	protected:
		virtual void updateObjects();
	public:
		SlideYTransition(CubesGroup& group);
		virtual ~SlideYTransition();

		void setSourceY(float value) { sourceY = value; }
	};

}
#endif
