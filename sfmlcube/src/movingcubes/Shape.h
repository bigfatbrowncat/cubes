/*
 * CubesGroup.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <list>

#include <SFML/System/NonCopyable.hpp>

#include "transitions/Transition.h"
#include "transitions/SlideXTransition.h"
#include "transitions/SlideYTransition.h"
#include "transitions/RotateTransition.h"
#include "Cube.h"

using namespace std;
using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Field;

		class Shape : public sf::NonCopyable
		{
			friend class transitions::SlideXTransition;
			friend class transitions::SlideYTransition;
			friend class transitions::RotateTransition;
		private:
			Field& field;
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
			Shape(Field& field) :
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
			}

			list<Cube>& getCubes() { return cubes; }

			void advanceStep(double delta);
			bool transitionIsInProgress() const;

			void moveVerticalNoTransition(int cells);
			void moveHorizontalNoTransition(int cells);
			void rotateNoTransition(int angle);

			void moveVertical(int cells, Transition::PhaseProcessingFunction function, float longitude);
			void moveHorizontal(int cells, Transition::PhaseProcessingFunction function, float longitude);
			void rotate(int angle, Transition::PhaseProcessingFunction function, float longitude);

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

			void glDraw(int dx, int dy);
		};
	}
}
#endif
