/*
 * ShapeWithKinematics.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef SHAPEWITHKINEMATICS_H_
#define SHAPEWITHKINEMATICS_H_

#include "VelocityController.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"
#include "../movingcubes/TimingManager.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class ShapeWithKinematics
		{
		protected:
			const VelocityController& velocityController;

			Shape shape;
			ShapeKinematics kinematics;

			int fallBy;
			bool blink;
		public:
			ShapeWithKinematics(TimingManager& timingManager,
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

			virtual ~ShapeWithKinematics();
		};
	}
}
#endif
