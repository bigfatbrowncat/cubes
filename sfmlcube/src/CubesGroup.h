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

using namespace std;

namespace sfmlcubes
{
	class CubesField;

	class CubesGroup : public sf::NonCopyable
	{
		friend class SlideXTransition;
		friend class SlideYTransition;
		friend class RotateTransition;
	private:
		CubesField& field;
		list<Cube> cubes;
		SlideXTransition horizontalTransition;
		SlideYTransition verticalTransition;
		RotateTransition rotateTransition;

		// Sliding
		float slidingX, slidingY;

		// Rotating animation
		CubeRotatingCenterType rotatingCenterType;
		int rotatingCenterX, rotatingCenterY;
		float rotatingAngle;	// 1 = 90 degrees

	public:
		CubesGroup(CubesField& field) :
			field(field),

			horizontalTransition(*this),
			verticalTransition(*this),
			rotateTransition(*this),

			slidingX(0),
		    slidingY(0),

		    rotatingCenterType(crctCenterOfCube),
		    rotatingCenterX(0),
		    rotatingCenterY(0),
		    rotatingAngle(0)
		{}

		list<Cube>& getCubes() { return cubes; }

		void advanceStep(double delta);

		void moveUpNoTransition();
		void moveDownNoTransition();
		void moveRightNoTransition();
		void moveLeftNoTransition();
		void rotateCWNoTransition(int angle);

		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void rotateCW(int angle);


		int getLeft();
		int getRight();
		int getTop();
		int getBottom();

		list<Cube*> cubeAt(int i, int j);

		void setRotatingCenter(int centerX, int centerY, CubeRotatingCenterType value)
		{
			rotatingCenterX = centerX;
			rotatingCenterY = centerY;
			rotatingCenterType = value;
		}

		int getRotatingCenterX() const { return rotatingCenterX; }
		int getRotatingCenterY() const { return rotatingCenterY; }
		CubeRotatingCenterType getRotatingCenterType() const { return rotatingCenterType; }

		void glDraw(int dx, int dy);
	};


}
#endif
