/*
 * FallingShapeController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include "FallingShapeController.h"

#include "../movingcubes/transitions/ArctangentPhaseProcessingFunction.h"
#include "../movingcubes/transitions/LinearPhaseProcessingFunction.h"


namespace sfmlcubes
{
	namespace controllers
	{
		using namespace sfmlcubes::movingcubes::transitions;

		FallingShapeController::FallingShapeController(TimingManager& timingManager, WallsController& wallsController, FallenController& fallenController, VelocityController& velocityController) :
			TimeDependent(timingManager),
			falling(timingManager),

			wallsController(wallsController),
			fallenController(fallenController),
			velocityController(velocityController),

			fallingKinematics(timingManager, falling),
			fallingDynamics(falling),

			fastFalling(false),
			movingRight(false),
			movingLeft(false),
			fallDownPending(false),
			rotatingCW(false),

			state(fscsFlying)
		{
			fallingDynamics.addObstacle(fallenController.getShape());
			fallingDynamics.addObstacle(wallsController.getShape());
		}

		void FallingShapeController::processTimeStep(double dt)
		{
			switch (state)
			{

			case fscsFlying:

				if (!fallingKinematics.isMovingHorizontally())
				{
					if (movingRight)
					{
						if (fallingDynamics.canMoveRight())
						{
							fallingKinematics.moveHorizontal(1, sfmlcubes::movingcubes::transitions::LinearPhaseProcessingFunction(), velocityController.getHorizontalMovingDuration());
						}
					}
					else if (movingLeft)
					{
						if (fallingDynamics.canMoveLeft())
						{
							fallingKinematics.moveHorizontal(-1, LinearPhaseProcessingFunction(), velocityController.getHorizontalMovingDuration());
						}
					}

				}

				if (!fallingKinematics.isMovingVertically())
				{
					if (fallDownPending || fastFalling)
					{
						bool canFallDown = false;
						if (fastFalling)
						{
							if (fallingDynamics.canMoveDown())
							{
								fallingKinematics.moveVertical(1, LinearPhaseProcessingFunction(), velocityController.getFallingDownFastDuration());
								canFallDown = true;
							}
						}
						else if (fallDownPending)
						{
							if (fallingDynamics.canMoveDown())
							{
								fallingKinematics.moveVertical(1, sfmlcubes::movingcubes::transitions::ArctangentPhaseProcessingFunction(), velocityController.getFallingDownDuration());
								canFallDown = true;
							}
							fallDownPending = false;
						}
						if (!canFallDown)
						{
							if (!fallingKinematics.isMovingHorizontally())
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

				if (!fallingKinematics.isRotating())
				{
					if (rotatingCW)
					{
						if (fallingDynamics.canRotate(1))
						{
							fallingKinematics.rotate(1, ArctangentPhaseProcessingFunction(), velocityController.getRotationLongitude());
						}
					}
				}
				break;
			case fscsLandingPending:
				if (!fallingKinematics.isMovingHorizontally())
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

		void FallingShapeController::launchNewShape(const ShapeCubes& shape)
		{
			falling.setCubes(shape);
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
