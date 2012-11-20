/*
 * CubesGroup.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef CUBESGROUP_H_
#define CUBESGROUP_H_

#include <list>

#include <SFML/System/NonCopyable.hpp>

#include "SlideXTransition.h"
#include "SlideYTransition.h"
#include "RotateTransition.h"

#include "Cube.h"
//#include "CubesField.h"

using namespace std;

namespace sfmlcubes
{
	class CubesField;

	class CubesGroup : public sf::NonCopyable
	{
	private:
		CubesField& field;
		list<Cube> cubes;
		SlideXTransition horizontalTransition;
		SlideYTransition verticalTransition;
		RotateTransition rotateTransition;
		CubeRotatingCenterType crct;
		int rotatingCenterX, rotatingCenterY;

		float rotatingLongitude;
		float movingLongitude;
	public:
		CubesGroup(CubesField& field) :
			field(field),

			horizontalTransition(*this),
			verticalTransition(*this),
			rotateTransition(*this),

			rotatingLongitude(0.25),
			movingLongitude(0.08)
		{}

		list<Cube>& getCubes() { return cubes; }

		void advanceStep(double delta);

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotateCW(int angle);

		int getLeft();
		int getRight();
		int getTop();
		int getBottom();

		Cube* cubeAt(int i, int j);

		void setRotatingCenter(int centerX, int centerY, CubeRotatingCenterType value)
		{
			rotatingCenterX = centerX;
			rotatingCenterY = centerY;
			crct = value;
		}

		void glDraw(int dx, int dy);
	};


}
#endif
