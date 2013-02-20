/*
 * ShapeKinematics.h
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#ifndef SHAPEKINEMATICS_H_
#define SHAPEKINEMATICS_H_

#include <SFML/System/NonCopyable.hpp>

#include "Shape.h"
#include "Parameter.h"
#include "transitions/PhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		using namespace transitions;

		class ShapeKinematics : sf::NonCopyable
		{
		private:
			Shape& shape;
		public:
			ShapeKinematics(Shape& shape);

			void processTimeStep(double delta);
			bool transitionIsInProgress() const;

			void moveVertical(int cells, const PhaseProcessingFunction& function, float longitude);
			void moveHorizontal(int cells, const PhaseProcessingFunction& function, float longitude);
			void rotate(int angle, const PhaseProcessingFunction& function, float longitude);
			void blink(float longitude, int blinks);

			bool isMovingHorizontally() const
			{
				return shape.slidingX->isChanging();
			}
			bool isMovingVertically() const
			{
				return shape.slidingY->isChanging();
			}
			bool isRotating() const
			{
				return shape.rotatingAngle->isChanging();
			}
			bool isBlinking() const
			{
				return shape.transparency->isChanging();
			}


/*			const Transition& getHorizontalTransition() const { return mHorizontalTransition; }
			const Transition& getVerticalTransition() const { return mVerticalTransition; }
			const Transition& getRotateTransition() const { return mRotateTransition; }
			const Transition& getBlinkingTransition() const { return mBlinkingTransition; }*/

			virtual ~ShapeKinematics();
		};

	}
}
#endif /* SHAPEKINEMATICS_H_ */
