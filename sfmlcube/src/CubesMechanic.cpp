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

#include "Logger.h"
#include "CubesMechanic.h"
#include "movingcubes/Shape.h"

using namespace std;

namespace sfmlcubes
{

	CubesMechanic::CubesMechanic(int width, int height):

			width(width), height(height),
			state(cmsBetweenShapes),
			wallsController(width, height),
			fallenController(1, 1, width - 2, height - 2),
			velocityController(),
			fallingShapeController(wallsController, fallenController, velocityController),
			scoreCounter(fallenController),

			time(0),
			momentWhenFallIssued(0),
			paused(false)
	{
	}

	CubesMechanic::~CubesMechanic() { }


	void CubesMechanic::processTimeStep(float dt)
	{
		if (!paused)
		{
			fallingShapeController.processTimeStep(dt);
			fallenController.processTimeStep(dt);

			time += dt;

			switch (state)
			{
			case cmsShapeFalling:

				if (time - momentWhenFallIssued > velocityController.getFallingPeriod())
				{
					fallingShapeController.fallDown();
					momentWhenFallIssued = time;
				}

				//if (fallingShapeController.getState() == fscsNew)
				{

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
					newShape.moveVerticalNoTransition(1);

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

	void CubesMechanic::turnOff(CubesMechanicCommand command)
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

	void CubesMechanic::turnOn(CubesMechanicCommand command)
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

	void CubesMechanic::glDraw(int dx, int dy)
	{
		wallsController.getShape().glDraw(dx, dy);
		fallingShapeController.getShape().glDraw(dx, dy);

		list<Shape> shps = fallenController.getShapes();

		for (list<Shape>::const_iterator iter = shps.begin();
		     iter != shps.end();
		     iter++)
		{
			(*iter).glDraw(dx, dy);
		}

	}
}
