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
		static float FALLING_DOWN_FIRED_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;
//		static float LINES_FIRING_LONGITUDE;
//		static float LINES_FIRING_BLINKING_PART;

		CubesField& field;
		list<Cube> cubes;
		SlideXTransition mHorizontalTransition;
		SlideYTransition mVerticalTransition;
		RotateTransition mRotateTransition;


		// Sliding
		float slidingX, slidingY;

		// Rotating animation
		CubeRotatingCenterType rotatingCenterType;
		int rotatingCenterX, rotatingCenterY;
		float rotatingAngle;	// 1 = 90 degrees
		sf::Color mTone;
	public:
		CubesGroup(CubesField& field) :
			field(field),

			mHorizontalTransition(*this),
			mVerticalTransition(*this),
			mRotateTransition(*this),

			slidingX(0),
		    slidingY(0),

		    rotatingCenterType(crctCenterOfCube),
		    rotatingCenterX(0),
		    rotatingCenterY(0),
		    rotatingAngle(0)
		{
			mHorizontalTransition.setFunction(Transition::ppfLinear);
			mHorizontalTransition.setLongitude(HORIZONTAL_MOVING_LONGITUDE);
			mVerticalTransition.setFunction(Transition::ppfArctangent);
			mVerticalTransition.setLongitude(FALLING_DOWN_LONGITUDE);
			mRotateTransition.setFunction(Transition::ppfArctangent);
			mRotateTransition.setLongitude(ROTATION_LONGITUDE);
		}

		list<Cube>& getCubes() { return cubes; }

		void advanceStep(double delta);
		bool transitionIsInProgress() const;

		void moveUpNoTransition();
		void moveDownNoTransition(int cells);
		void moveRightNoTransition();
		void moveLeftNoTransition();
		void rotateCWNoTransition(int angle);

		void moveUp();
		void moveDown(int cells);
		void moveDownFast();
		void moveDownFired(int cells);
		void moveDownFalling();

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

		const SlideXTransition& getHorizontalTransition() const { return mHorizontalTransition; }
		const SlideYTransition& getVerticalTransition() const { return mVerticalTransition; }
		const RotateTransition& getRotateTransition() const { return mRotateTransition; }

		SlideXTransition& horizontalTransition() { return mHorizontalTransition; }
		SlideYTransition& verticalTransition() { return mVerticalTransition; }
		RotateTransition& rotateTransition() { return mRotateTransition; }

		sf::Color& tone() { return this->mTone; }
		void glDraw(int dx, int dy);
	};


}
#endif
