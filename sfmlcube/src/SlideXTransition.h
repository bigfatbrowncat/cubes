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
	class SlideXTransition : public Transition
	{
	private:
		float sourceX;
	protected:
		virtual void updateObjects();
	public:
		SlideXTransition(CubesGroup& group);
		virtual ~SlideXTransition();

		void setSourceX(float value) { sourceX = value; }
	};

}
#endif
