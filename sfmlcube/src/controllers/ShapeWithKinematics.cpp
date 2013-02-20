/*
 * ShapeWithKinematics.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "ShapeWithKinematics.h"

#include "../movingcubes/transitions/ParabolicPhaseProcessingFunction.h"
#include "../Logger.h"

namespace sfmlcubes
{
	namespace controllers
	{
		ShapeWithKinematics::ShapeWithKinematics(TimingManager& timingManager,
                                                 const VelocityController& velocityController) :
			velocityController(velocityController),
			shape(timingManager),
			kinematics(timingManager, shape),
			blink(false),
			fallBy(0)

		{

		}

		bool ShapeWithKinematics::isBlinkingInProgress() const
		{
			return kinematics.isBlinking();
		}

		bool ShapeWithKinematics::isMovingInProgress() const
		{
			return kinematics.isMovingVertically();
		}

		void ShapeWithKinematics::startAnimation()
		{
			if (blink)
			{
				if (kinematics.isBlinking())
				{
					Logger::DEFAULT.logWarning("try to start blinking twice");
				}

				kinematics.blink(velocityController.getBlinkingLongitude(), 3);
			}

			if (fallBy != 0)
			{
				if (kinematics.isMovingVertically())
				{
					Logger::DEFAULT.logWarning("try to start moving twice");
				}

				kinematics.moveVertical(fallBy, ParabolicPhaseProcessingFunction(), velocityController.getFallingDownFiredDuration());
			}
		}

		bool ShapeWithKinematics::isEmpty() const
		{
			return shape.getCubes().isEmpty();
		}

		ShapeWithKinematics::~ShapeWithKinematics()
		{

		}
	}
}
