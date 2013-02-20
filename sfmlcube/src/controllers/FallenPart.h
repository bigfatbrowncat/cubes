/*
 * ShapeWithKinematics.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef FALLENPART_H_
#define FALLENPART_H_

#include "VelocityController.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"
#include "../movingcubes/TimingManager.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class FallenPart
		{
		protected:
			const VelocityController& velocityController;

			Shape shape;
			ShapeKinematics kinematics;

			int fallBy;
			bool blink;
		public:
			FallenPart(TimingManager& timingManager,
			                    const VelocityController& velocityController);

/*			Shape& takeShape() { return shape; }
			ShapeKinematics& takeKinematics() { return kinematics; }
			const ShapeKinematics& getKinematics() const { return kinematics; }*/

			void setBlink(bool value) { blink = value; }
			bool getBlink() { return blink; }
			void setFallBy(int value) { fallBy = value; }
			int getFallBy() { return fallBy; }

			bool isBlinkingInProgress() const;
			bool isMovingInProgress() const;
			void startAnimation();

			bool isEmpty() const;

			const Shape& getShape() const { return shape; }

			virtual ~FallenPart();
		};
	}
}
#endif
