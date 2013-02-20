/*
 * ShapeWithKinematics.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "FallenPart.h"

#include "../movingcubes/transitions/ParabolicPhaseProcessingFunction.h"
#include "../Logger.h"

namespace sfmlcubes
{
	namespace controllers
	{
		FallenPart::FallenPart(TimingManager& timingManager,
                                                 const VelocityController& velocityController) :
			velocityController(velocityController),
			shape(timingManager),
			kinematics(timingManager, shape),
			blink(false),
			fallBy(0)

		{

		}

		bool FallenPart::isBlinkingInProgress() const
		{
			return kinematics.isBlinking();
		}

		bool FallenPart::isMovingInProgress() const
		{
			return kinematics.isMovingVertically();
		}

		void FallenPart::startAnimation()
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

		bool FallenPart::isEmpty() const
		{
			return shape.getCubes().isEmpty();
		}

		FallenPart::~FallenPart()
		{

		}
	}
}
