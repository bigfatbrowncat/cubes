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
			TimingManager& timingManager;
			Shape& shape;
		public:
			ShapeKinematics(TimingManager& timingManager, Shape& shape);

			bool transitionIsInProgress() const;

			void moveVertical(int cells, const PhaseProcessingFunction& function, float longitude);
			void moveHorizontal(int cells, const PhaseProcessingFunction& function, float longitude);
			void rotate(int angle, const PhaseProcessingFunction& function, float longitude);
			void blink(float longitude, int blinks);

			bool isMovingHorizontally() const
			{
				return shape.getSlidingXParameter().isChanging();
			}
			bool isMovingVertically() const
			{
				return shape.getSlidingYParameter().isChanging();
			}
			bool isRotating() const
			{
				return shape.getRotatingAngleParameter().isChanging();
			}
			bool isBlinking() const
			{
				return shape.getTransparencyParameter().isChanging();
			}

			virtual ~ShapeKinematics();
		};

	}
}
#endif /* SHAPEKINEMATICS_H_ */
