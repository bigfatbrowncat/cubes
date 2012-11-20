/*
 * SlideTransition.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef ROTATETRANSITION_H_
#define ROTATETRANSITION_H_

#include "Transition.h"
//#include "CubesGroup.h"
#include "CubeRotatingCenterType.h"

namespace sfmlcubes
{
	class CubesGroup;

	class RotateTransition : public Transition
	{
	private:
		int sourceAngle;
		int rotatingCenterX, rotatingCenterY;
		CubeRotatingCenterType rotatingCenterType;
	protected:
		virtual void updateObjects();
	public:
		RotateTransition() {}
		RotateTransition(CubesGroup& group);
		virtual ~RotateTransition();

		void setSourceAngle(int value);
		void setRotatingCenter(int x, int y, CubeRotatingCenterType crct);
	};

}
#endif
