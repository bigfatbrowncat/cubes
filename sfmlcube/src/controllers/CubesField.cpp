/*
 * CubesMechanic.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>

#include "../Logger.h"
#include "CubesField.h"
#include "../movingcubes/Shape.h"

using namespace std;

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		CubesField::CubesField(int width, int height, int visibleHeight):

				width(width), height(height),
				state(cmsBetweenShapes),
				velocityController(),
				wallsController(velocityController, width, height, visibleHeight),
				fallenController(wallsController, velocityController, 0, height - 2, visibleHeight,  1, width - 2),
				fallingShapeController(wallsController, fallenController, velocityController),
				scoreCounter(fallenController, wallsController),

				time(0),
				momentWhenFallIssued(0),
				paused(false)
		{
		}

		CubesField::~CubesField() { }


		void CubesField::processTimeStep(float dt)
		{
			if (!paused)
			{
				fallingShapeController.processTimeStep(dt);
				fallenController.processTimeStep(dt);
				wallsController.processTimeStep(dt);

				time += dt;

				switch (state)
				{
				case cmsShapeFalling:

					if (time - momentWhenFallIssued > velocityController.getFallingPeriod())
					{
						fallingShapeController.fallDown();
						momentWhenFallIssued = time;
					}

					if (fallingShapeController.getState() == fscsLanded)
					{
						scoreCounter.beforeShapeFallen(fallingShapeController.getShape());

						// Desaturating the shape
						Shape falling = fallingShapeController.getShape();
						falling.changeToFallenColor();

						// Merging
						fallenController.mergeShape(falling);
						fallingShapeController.clearShape();
						scoreCounter.afterShapeFallen();
						fallenController.fireFullLines();

						// Multiplying the velocity
						velocityController.advanceStep();

						state = cmsBetweenShapes;
					}

					break;

				case cmsBetweenShapes:
					// Checking if the fallen shape controller finished it's tasks
					if (fallenController.getState() == FallenController::sPassive)
					{
						scoreCounter.linesHasBeenFired();
						// Dealing the new shape
						Shape newShape = shapeDealer.dealNext();
						// Positioning it to the top-center of the game field
						newShape.moveHorizontalNoTransition(6);
						//newShape.moveVerticalNoTransition(0);

						// Checking for collisions
						if (fallenController.anyCollisionsWithRemainingLines(newShape))
						{
							// Our new shape collides with the fallen ones.
							// That means the game is over
							state = cmsGameOver;
						}
						else
						{
							// Launching the new shape as a falling one
							fallingShapeController.launchNewShape(newShape);
							// Moving the new shape down for the first time
							fallingShapeController.fallDown();
							momentWhenFallIssued = time;

							state = cmsShapeFalling;
						}

					}
					break;

				case cmsGameOver:
					// Doing nothing
					break;
				}
			}
		}

		void CubesField::turnOff(CubesMechanicCommand command)
		{
			switch (command)
			{
			case cmcMoveDownFast:
				fallingShapeController.turnOffFastFalling();
				break;
			case cmcMoveLeft:
				fallingShapeController.turnOffLeft();
				break;
			case cmcMoveRight:
				fallingShapeController.turnOffRight();
				break;
			case cmcRotateCW:
				fallingShapeController.turnOffRotateCW();
				break;
			case cmcPause:
				paused = false;
				break;
			}
		}

		void CubesField::turnOn(CubesMechanicCommand command)
		{
			switch (command)
			{
			case cmcMoveDownFast:
				fallingShapeController.turnOnFastFalling();
				break;
			case cmcMoveLeft:
				fallingShapeController.turnOnLeft();
				break;
			case cmcMoveRight:
				fallingShapeController.turnOnRight();
				break;
			case cmcRotateCW:
				fallingShapeController.turnOnRotateCW();
				break;
			case cmcPause:
				paused = true;
				break;
			}
		}

	}
}
