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
		CubesField::CubesField(int width, int height, int visibleFrame):

				width(width), height(height),
				state(cmsBetweenShapes),
				velocityController(),
				wallsController(velocityController, width, height, visibleFrame),
				fallenController(wallsController, velocityController, 0, height - 2, height + visibleFrame,  1, width - 2),
				fallingShapeController(wallsController, fallenController, velocityController),
				scoreCounter(fallenController, wallsController),

				time(0),
				momentWhenFallIssued(0),
				paused(false)
		{
		}

		CubesField::~CubesField() { }

		Shape CubesField::findProperPosition(const Shape& shape)
		{
			Shape best, proper;
			for (int i = width; i >= 0; i--)
			{
				Shape test = shape;
				int x = width / 2 + (i % 2 == 0 ? 1 : -1) * (i / 2);

				test.moveHorizontalNoTransition(x);

				Shape testD = test;
				testD.moveVerticalNoTransition(1);

				Shape testDD = testD;
				testD.moveVerticalNoTransition(1);

				// Checking for collisions
				if (!fallenController.anyCollisionsWithRemainingLines(test)  && !wallsController.anyCollisions(test) &&
				    !fallenController.anyCollisionsWithRemainingLines(testD) && !wallsController.anyCollisions(testD))
				{
					if (!fallenController.anyCollisionsWithRemainingLines(testDD) && !wallsController.anyCollisions(testDD))
					{
						best = test;
					}
					else
					{
						proper = test;
					}
				}

			}
			if (!best.isEmpty())
			{
				return best;
			}
			else
			{
				return proper;
			}
		}

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
						Shape dealedShape = shapeDealer.dealNext();
						// Positioning it to the top-center of the game field

						Shape newShape = findProperPosition(dealedShape);

						// Checking if the positioning succeeded
						if (newShape.isEmpty())
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
