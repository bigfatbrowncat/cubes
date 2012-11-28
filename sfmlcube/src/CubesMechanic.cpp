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
	float CubesMechanic::FALLING_PERIOD = 1.0;

	CubesMechanic::CubesMechanic(int width, int height):
			width(width), height(height),
			state(cmsShapeFalling),
			wallsController(width, height),
			fallenController(1, 1, width - 2, height - 2),
			fallingShapeController(wallsController, fallenController),

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

				if (time - momentWhenFallIssued > FALLING_PERIOD)
				{
					fallingShapeController.fallDown();
					momentWhenFallIssued = time;
				}

				if (fallingShapeController.getState() == fscsLanded)
				{
					fallenController.mergeShape(fallingShapeController.getShape());
					fallingShapeController.clearShape();
					fallenController.fireFullLines();
					state = cmsLinesFiring;
				}

				break;

			case cmsLinesFiring:
				if (fallenController.getState() == FallenController::sPassive)
				{
					if (fallingShapeController.createNewShape())
					{
						momentWhenFallIssued = time;
						state = cmsShapeFalling;
					}
					else
					{
						state = cmsGameOver;
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
