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
		static float ROTATION_LONGITUDE;
		static float FALLING_DOWN_LONGITUDE;
		static float FALLING_DOWN_FAST_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;
//		static float LINES_FIRING_LONGITUDE;
//		static float LINES_FIRING_BLINKING_PART;

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
		{
			horizontalTransition.setFunction(Transition::ppfLinear);
			horizontalTransition.setLongitude(HORIZONTAL_MOVING_LONGITUDE);
			verticalTransition.setFunction(Transition::ppfArctangent);
			verticalTransition.setLongitude(FALLING_DOWN_LONGITUDE);
			rotateTransition.setFunction(Transition::ppfArctangent);
			rotateTransition.setLongitude(ROTATION_LONGITUDE);
		}

		list<Cube>& getCubes() { return cubes; }

		void advanceStep(double delta);
		bool transitionIsInProgress() const;

		void moveUpNoTransition();
		void moveDownNoTransition();
		void moveRightNoTransition();
		void moveLeftNoTransition();
		void rotateCWNoTransition(int angle);

		void moveUp();
		void moveDown(bool fast);
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

		const SlideXTransition& getHorizontalTransition() const { return horizontalTransition; }
		const SlideYTransition& getVerticalTransition() const { return verticalTransition; }
		const RotateTransition& getRotateTransition() const { return rotateTransition; }

		void glDraw(int dx, int dy);
	};


}
#endif
