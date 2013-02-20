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
		CubesField::CubesField(TimingManager& timingManager, int width, int height, int visibleFrame):
				TimeDependent(timingManager),

				width(width), height(height),
				state(cmsBetweenShapes),
				velocityController(),
				wallsController(timingManager, velocityController, width, height, visibleFrame),
				fallenController(timingManager, wallsController, velocityController, 0, height - 2, height + visibleFrame,  1, width - 2),
				fallingShapeController(timingManager, wallsController, fallenController, velocityController),
				scoreCounter(fallenController, wallsController),

				time(0),
				momentWhenFallIssued(0),
				paused(false)
		{
		}

		CubesField::~CubesField() { }

		ShapeCubes CubesField::findProperPosition(const ShapeCubes& shape)
		{
			ShapeCubes best, proper;
			for (int i = width; i >= 0; i--)
			{
				ShapeCubes test = shape;
				int x = width / 2 + (i % 2 == 0 ? 1 : -1) * (i / 2);

				test.moveHorizontalNoTransition(x);

				ShapeCubes testD = test;
				testD.moveVerticalNoTransition(1);

				ShapeCubes testDD = testD;
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

		void CubesField::processTimeStep(double dt)
		{
			if (!paused)
			{
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
						scoreCounter.beforeShapeFallen(fallingShapeController.getShape().getCubes());

						// Desaturating the shape
						Shape falling = fallingShapeController.getShape();

						ShapeCubes sc = falling.getCubes();
						sc.changeToFallenColor();
						falling.setCubes(sc);

						// Merging
						fallenController.mergeShape(falling.getCubes());
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
						ShapeCubes dealedShape = shapeDealer.dealNext();
						// Positioning it to the top-center of the game field

						ShapeCubes newShape = findProperPosition(dealedShape);

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
