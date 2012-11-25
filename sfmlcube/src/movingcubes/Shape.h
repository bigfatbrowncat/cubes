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
		private:
			Field& field;
			list<Cube> cubes;
			Transition mHorizontalTransition;
			Transition mVerticalTransition;
			Transition mRotateTransition;
			Transition mBlinkingTransition;

			// ** Animations **
			// Sliding
			float slidingX, slidingY;
			// Rotating animation
			Cube::RotatingCenterType rotatingCenterType;
			int rotatingCenterX, rotatingCenterY;
			float rotatingAngle;	// 1 = 90 degrees

			// Ambient color
			sf::Color ambientStatic;
			sf::Color ambientDynamic;
			float transparency;
		public:
			Shape(Field& field) :
				field(field),

				mBlinkingTransition(1, Transition::ppfConstant, 1),

				slidingX(0),
				slidingY(0),

				rotatingCenterType(Cube::rctCenter),
				rotatingCenterX(0),
				rotatingCenterY(0),
				rotatingAngle(0),

				ambientStatic(128, 128, 128, 255),
				ambientDynamic(255, 255, 255, 255),
				transparency(1.0)
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
			void blink(float longitude, int blinks);

			int getLeft();
			int getRight();
			int getTop();
			int getBottom();

			list<Cube*> cubeAt(int i, int j);

			void setRotatingCenter(int centerX, int centerY, Cube::RotatingCenterType value)
			{
				rotatingCenterX = centerX;
				rotatingCenterY = centerY;
				rotatingCenterType = value;
			}

			int getRotatingCenterX() const { return rotatingCenterX; }
			int getRotatingCenterY() const { return rotatingCenterY; }
			Cube::RotatingCenterType getRotatingCenterType() const { return rotatingCenterType; }

			const Transition& getHorizontalTransition() const { return mHorizontalTransition; }
			const Transition& getVerticalTransition() const { return mVerticalTransition; }
			const Transition& getRotateTransition() const { return mRotateTransition; }
			const Transition& getBlinkingTransition() const { return mBlinkingTransition; }

			void glDraw(int dx, int dy);
		};
	}
}
#endif
