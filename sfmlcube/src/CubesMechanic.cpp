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
	float CubesMechanic::FALLING_DOWN_FIRED_LONGITUDE = 0.3;
	float CubesMechanic::BLINKING_LONGITUDE = 0.6;
	float CubesMechanic::FALLING_PERIOD = 1.0;

	CubesMechanic::CubesMechanic(int width, int height):
			width(width), height(height),
			state(cmsShapeFalling),
			wallsController(width, height),
			fallenController(),
			fallingShapeController(wallsController, fallenController)
	{
	}

	CubesMechanic::~CubesMechanic() { }


/*	bool CubesMechanic::countLinesToFire()
	{
		linesToFire.clear();
		for (int j = 0; j < field.getHeight(); j++)
		{
			bool thisRowIsFull = true;
			for (int i = 0; i < field.getWidth(); i++)
			{
				if (field.cubeAt(i, j).empty()) thisRowIsFull = false;
			}
			if (thisRowIsFull)
			{
				linesToFire.push_back(j);
			}
		}
		return linesToFire.size() > 0;
	}

	void CubesMechanic::collectLinesToFire()
	{
		bool lastLineWasFired = true;
		int count = 0;
		for (int j = field.getHeight() - 1; j >= count; j--)
		{

			// Check if this line is full
			bool thisRowIsFull = true;
			for (int i = 1; i < field.getWidth() - 1; i++)
			{
				if (fallen.cubeAt(i, j).empty()) thisRowIsFull = false;
			}

			if (thisRowIsFull)
			{
				// First of all we close the recent group if it exists
				if (!lastLineWasFired && firingGroups.size() > 0)
				{
					firingLineCounts.insert(pair<ShapeKinematics*, int> (firingGroupsDynamics.back(), count) );
				}

				count ++;
				lastLineWasFired = true;
			}
			else
			{
				// This line isn't fired
				if (lastLineWasFired)
				{
					// The last line was fired, so we start a new group

					// and then we create a new one
					Shape* s = new Shape();
					ShapeKinematics* sd = new ShapeKinematics();
					sd->setShape(*s);

					firingGroups.push_back(s);
					firingGroupsDynamics.push_back(sd);
				}

				// Adding the line to the current group
				for (int i = 1; i < field.getWidth() - 1; i++)
				{
					if (!fallen.cubeAt(i, j).empty())
					{
						// Adding the cube to the current firing group
						firingGroups.back()->getCubes().push_back(*(fallen.cubeAt(i, j).back()));
						// Removing the cube from the fallens
						fallen.getCubes().remove(*(fallen.cubeAt(i, j).back()));
					}
				}
				lastLineWasFired = false;
			}
		}

		// close the last group
		if (firingGroups.size() > 0)
		{
			if (count > 0)
			{
				firingLineCounts.insert(pair<ShapeKinematics*, int> (firingGroupsDynamics.back(), count) );
			}
				//firingGroups.back()->moveVertical(count, Transition::ppfParabolic, FALLING_DOWN_FIRED_LONGITUDE);
		}

		//linesFired += count;

		// Adding the new groups to our board
		for (list<Shape*>::iterator iter = firingGroups.begin(); iter != firingGroups.end(); iter++)
		{
			field.getCubesGroups().push_back(*iter);
		}

		if (count > 0)
		{
			// Starting the blinking of the firing lines
			fallenKinematics.blink(BLINKING_LONGITUDE, 3);
			state = cmsLinesToFireBlinking;
		}
		else
		{
			state = cmsLinesFiring;
		}
	}

	void CubesMechanic::removeFiredAwayLines()
	{
		for (map<ShapeKinematics*, int>::iterator iter = firingLineCounts.begin(); iter != firingLineCounts.end(); iter++)
		{
			(*iter).first->moveVertical((*iter).second, Transition::ppfParabolic, FALLING_DOWN_FIRED_LONGITUDE);
			linesFired += (*iter).second;
		}

		// Clearing the fallen part of the board
		fallen.getCubes().clear();
	}

	bool CubesMechanic::anyFiringTransitionsInProgress()
	{
		for (list<ShapeKinematics*>::iterator iter = firingGroupsDynamics.begin(); iter != firingGroupsDynamics.end(); iter++)
		{
			if ((*iter)->transitionIsInProgress()) return true;
		}
		return false;
	}

	void CubesMechanic::firingGroupsToFallen()
	{
		while (firingGroups.size() > 0)
		{
			Shape* cg = firingGroups.back();

			for (list<Cube>::iterator iter = cg->getCubes().begin(); iter != cg->getCubes().end(); iter++)
			{
				fallen.getCubes().push_back(*iter);
			}

			field.getCubesGroups().remove(cg);
			firingGroups.remove(cg);
			delete cg;
		}

		while (firingGroupsDynamics.size() > 0)
		{
			ShapeKinematics* kin = firingGroupsDynamics.back();
			firingGroupsDynamics.remove(kin);
			firingLineCounts.erase(kin);
			delete kin;
		}
	}
*/
	void CubesMechanic::processTimeStep(float dt)
	{
		/*fallingKinematics.advanceStep(dt);
		fallenKinematics.advanceStep(dt);
		for (list<ShapeKinematics*>::iterator iter = firingGroupsDynamics.begin(); iter != firingGroupsDynamics.end(); iter++)
		{
			(*iter)->advanceStep(dt);
		}*/
		//field.advanceStep(dt);

		fallingShapeController.processTimeStep(dt);

		time += dt;

		switch (state)
		{
		case cmsShapeFalling:
			if (time - momentWhenFallIssued > FALLING_PERIOD)
			{
				fallingShapeController.fallDown();
				momentWhenFallIssued = time;
			}


			break;
		case cmsLinesToFireBlinking:
/*			if (!fallenKinematics.getBlinkingTransition().isInProgress())
			{
				removeFiredAwayLines();
				state = cmsLinesFiring;
			}
*/
			break;
		case cmsLinesFiring:
/*			if (!anyFiringTransitionsInProgress())
			{
				firingGroupsToFallen();
				if (createNewBlock())
				{
					momentWhenFallIssued = time;
					state = cmsShapeFalling;
				}
				else
				{
					state = cmsGameOver;
				}
			}*/
			break;

		case cmsGameOver:
			// Doing nothing
			break;
		}
	}


/*	void CubesMechanic::freezeFalling()
	{
		for (list<Cube>::iterator iter = falling.getCubes().begin(); iter != falling.getCubes().end(); iter++)
		{
			fallen.getCubes().push_back(*iter);
		}
		falling.getCubes().clear();
	}*/

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
		}
	}
}
