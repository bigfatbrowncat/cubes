/*
 * FallingShapeController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include "FallingShapeController.h"

namespace sfmlcubes
{
	namespace controllers
	{
		FallingShapeController::FallingShapeController(WallsController& wallsController, FallenController& fallenController, VelocityController& velocityController) :
			wallsController(wallsController),
			fallenController(fallenController),
			velocityController(velocityController),

			fallingKinematics(*this),
			fallingDynamics(*this),

			fastFalling(false),
			movingRight(false),
			movingLeft(false),
			fallDownPending(false),
			rotatingCW(false),

			state(fscsFlying)
		{
			fallingDynamics.addObstacle(fallenController);
			fallingDynamics.addObstacle(wallsController);
		}

		void FallingShapeController::processTimeStep(float dt)
		{
			fallingKinematics.advanceStep(dt);

			switch (state)
			{

			case fscsFlying:

				if (!fallingKinematics.getHorizontalTransition().isInProgress())
				{
					if (movingRight)
					{
						if (fallingDynamics.canMoveRight())
						{
							fallingKinematics.moveHorizontal(1, Transition::ppfLinear, velocityController.getHorizontalMovingLongitude());
						}
					}
					else if (movingLeft)
					{
						if (fallingDynamics.canMoveLeft())
						{
							fallingKinematics.moveHorizontal(-1, Transition::ppfLinear, velocityController.getHorizontalMovingLongitude());
						}
					}

				}

				if (!fallingKinematics.getVerticalTransition().isInProgress())
				{
					if (fallDownPending || fastFalling)
					{
						bool canFallDown = false;
						if (fastFalling)
						{
							if (fallingDynamics.canMoveDown())
							{
								fallingKinematics.moveVertical(1, Transition::ppfLinear, velocityController.getFallingDownFastLongitude());
								canFallDown = true;
							}
						}
						else if (fallDownPending)
						{
							if (fallingDynamics.canMoveDown())
							{
								fallingKinematics.moveVertical(1, Transition::ppfArctangent, velocityController.getFallingDownLongitude());
								canFallDown = true;
							}
							fallDownPending = false;
						}
						if (!canFallDown)
						{
							if (!fallingKinematics.getHorizontalTransition().isInProgress())
							{
								state = fscsLanded;
							}
							else
							{
								state = fscsLandingPending;
							}
							break;
						}
					}
				}

				if (!fallingKinematics.getRotateTransition().isInProgress())
				{
					if (rotatingCW)
					{
						if (fallingDynamics.canRotate(1))
						{
							fallingKinematics.rotate(1, Transition::ppfArctangent, velocityController.getRotationLongitude());
						}
					}
				}
				break;
			case fscsLandingPending:
				if (!fallingKinematics.getHorizontalTransition().isInProgress())
				{
					state = fscsLanded;
				}
				break;
			case fscsLanded:
				// Do nothing
				break;
			}

		}

		void FallingShapeController::fallDown()
		{
			fallDownPending = true;
		}
		void FallingShapeController::turnOnFastFalling()
		{
			fastFalling = true;
		}
		void FallingShapeController::turnOnRight()
		{
			movingRight = true;
		}
		void FallingShapeController::turnOnLeft()
		{
			movingLeft = true;
		}
		void FallingShapeController::turnOnRotateCW()
		{
			rotatingCW = true;
		}
		void FallingShapeController::turnOffFastFalling()
		{
			fastFalling = false;
		}
		void FallingShapeController::turnOffRight()
		{
			movingRight = false;
		}
		void FallingShapeController::turnOffLeft()
		{
			movingLeft = false;
		}
		void FallingShapeController::turnOffRotateCW()
		{
			rotatingCW = false;
		}

		void FallingShapeController::launchNewShape(const Shape& shape)
		{
			falling = shape;
			state = fscsFlying;
		}

		void FallingShapeController::clearShape()
		{
			falling.clear();
		}

		FallingShapeController::~FallingShapeController()
		{
		}
	}
}
