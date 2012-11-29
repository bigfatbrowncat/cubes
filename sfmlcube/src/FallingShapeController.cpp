/*
 * FallingShapeController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include "FallingShapeController.h"

namespace sfmlcubes
{
	float FallingShapeController::ROTATION_LONGITUDE = 0.25;
	float FallingShapeController::FALLING_DOWN_LONGITUDE = 0.1;
	float FallingShapeController::FALLING_DOWN_FAST_LONGITUDE = 0.05;
	float FallingShapeController::HORIZONTAL_MOVING_LONGITUDE = 0.08;


	FallingShapeController::FallingShapeController(WallsController& wallsController, FallenController& fallenController) :
		wallsController(wallsController),
		fallenController(fallenController),

		fallingKinematics(*this),
		fallingDynamics(*this),

		state(fscsLanded)
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
						fallingKinematics.moveHorizontal(1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
					}
				}
				else if (movingLeft)
				{
					if (fallingDynamics.canMoveLeft())
					{
						fallingKinematics.moveHorizontal(-1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
					}
				}

			}

			if (!fallingKinematics.getVerticalTransition().isInProgress())
			{
				if (fallDownPending || fastFalling)
				{
					bool canFallDown = false;
					if (fallDownPending)
					{
						if (fallingDynamics.canMoveDown())
						{
							fallingKinematics.moveVertical(1, Transition::ppfArctangent, FALLING_DOWN_LONGITUDE);
							canFallDown = true;
						}
						fallDownPending = false;
					}
					else if (fastFalling)
					{
						if (fallingDynamics.canMoveDown())
						{
							fallingKinematics.moveVertical(1, Transition::ppfLinear, FALLING_DOWN_FAST_LONGITUDE);
							canFallDown = true;
						}
					}
					if (!canFallDown)
					{
						state = fscsLanded;
					}
				}
			}

			if (!fallingKinematics.getRotateTransition().isInProgress())
			{
				if (rotatingCW)
				{
					if (fallingDynamics.canRotate(1))
					{
						fallingKinematics.rotate(1, Transition::ppfArctangent, ROTATION_LONGITUDE);
					}
				}
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
