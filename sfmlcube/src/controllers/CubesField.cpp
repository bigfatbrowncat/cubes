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
		CubesField::CubesField(int width, int height):

				width(width), height(height),
				state(cmsBetweenShapes),
				wallsController(width, height),
				fallenController(1, 0, width - 2, height - 2),
				velocityController(),
				fallingShapeController(wallsController, fallenController, velocityController),
				scoreCounter(fallenController),

				cubePainter(CubePainter::uField),
				shapePainter(cubePainter),

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
				scoreCounter.processTimeStep(dt);

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
						scoreCounter.beforeShapeFallen();
						fallenController.mergeShape(fallingShapeController.getShape());
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
						if (fallenController.anyCollisions(newShape))
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

		void CubesField::glDraw() const
		{
			shapePainter.paint(wallsController.getShape());
			shapePainter.paint(fallingShapeController.getShape());

			list<Shape> shps = fallenController.getShapes();

			for (list<Shape>::const_iterator iter = shps.begin();
				 iter != shps.end();
				 iter++)
			{
				shapePainter.paint(*iter);
			}

		}
	}
}
