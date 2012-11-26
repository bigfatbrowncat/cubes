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
	float CubesMechanic::ROTATION_LONGITUDE = 0.25;
	float CubesMechanic::FALLING_DOWN_LONGITUDE = 0.1;
	float CubesMechanic::FALLING_DOWN_FAST_LONGITUDE = 0.05;
	float CubesMechanic::FALLING_DOWN_FIRED_LONGITUDE = 0.3;
	float CubesMechanic::HORIZONTAL_MOVING_LONGITUDE = 0.08;
	float CubesMechanic::BLINKING_LONGITUDE = 0.6;
	float CubesMechanic::FALLING_PERIOD = 1.0;

	CubesMechanic::CubesMechanic(int width, int height):
			state(cmsShapeFalling),
			field(width, height),
			walls(field),
			falling(field),
			fallen(field),

			horizontalDirection(cmhdNone),
			verticalDirection(cmvdNone),
			rotationDirection(cmrdNone)

			//verticalMovingDirection(cmvdNone),
			//horizontalMovingDirection(cmhdNone)

	{
		field.getCubesGroups().push_back(&walls);
		field.getCubesGroups().push_back(&fallen);
		field.getCubesGroups().push_back(&falling);

		sf::Color wallColor = sf::Color(96, 96, 96);

		for (int i = 0; i < field.getWidth(); i++)
		{
			walls.getCubes().push_back(Cube(i, field.getHeight() - 1, Cube::mtWall, wallColor));
		}
		for (int j = 1; j < field.getHeight(); j++)
		{
			walls.getCubes().push_back(Cube(0, j, Cube::mtWall, wallColor));
			walls.getCubes().push_back(Cube(field.getWidth() - 1, j, Cube::mtWall, wallColor));
		}
	}

	CubesMechanic::~CubesMechanic() { }

	bool CubesMechanic::anyCollisions()
	{
		for (list<Cube>::const_iterator citer = falling.getCubes().begin(); citer != falling.getCubes().end(); citer++)
		{
			int i = (*citer).x;
			int j = (*citer).y;

			// Checking if there is a cube or a wall under our cube
			if (!fallen.cubeAt(i, j).empty() ||
			    !walls.cubeAt(i, j).empty()) return true;
		}

		return false;
	}

	bool CubesMechanic::canMoveDownFalling()
	{
		falling.moveVerticalNoTransition(1);
		bool res = !anyCollisions();
		falling.moveVerticalNoTransition(-1);

		return res;
	}

	bool CubesMechanic::canMoveLeftFalling()
	{
		falling.moveHorizontalNoTransition(-1);
		bool res = !anyCollisions();
		falling.moveHorizontalNoTransition(1);

		return res;
	}

	bool CubesMechanic::canMoveRightFalling()
	{
		falling.moveHorizontalNoTransition(1);
		bool res = !anyCollisions();
		falling.moveHorizontalNoTransition(-1);

		return res;
	}

	bool CubesMechanic::canRotateFalling(int angle)
	{
		falling.rotateNoTransition(angle);
		bool res = !anyCollisions();
		falling.rotateNoTransition(-angle);

		return res;
	}

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
	}*/

	void CubesMechanic::collectLinesToFire()
	{
		firingGroups.clear();
		firingLineCounts.clear();

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
					firingLineCounts.insert(pair<Shape*, int> (firingGroups.back(), count) );
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
					firingGroups.push_back(new Shape(field));
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
				firingLineCounts.insert(pair<Shape*, int> (firingGroups.back(), count) );
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
			fallen.blink(BLINKING_LONGITUDE, 3);
			state = cmsLinesToFireBlinking;
		}
		else
		{
			state = cmsLinesFiring;
		}
	}

	void CubesMechanic::removeFiredAwayLines()
	{
		for (map<Shape*, int>::iterator iter = firingLineCounts.begin(); iter != firingLineCounts.end(); iter++)
		{
			(*iter).first->moveVertical((*iter).second, Transition::ppfParabolic, FALLING_DOWN_FIRED_LONGITUDE);
			linesFired += (*iter).second;
		}

		// Clearing the fallen part of the board
		fallen.getCubes().clear();
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
	}

	void CubesMechanic::processTimeStep(float dt)
	{
		field.advanceStep(dt);
		time += dt;
		if (time - momentWhenFallIssued > FALLING_PERIOD)
		{
			turnOn(cmcMoveDown);
			momentWhenFallIssued = time;
		}

		switch (state)
		{
		case cmsShapeFalling:

			// We can move vertically, horizontally and rotate at the same time,
			// so let's check our states and run commands

			if (!falling.getHorizontalTransition().isInProgress())
			{
				if (horizontalDirection == cmhdRight)
				{
					if (canMoveRightFalling())
					{
						falling.moveHorizontal(1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
					}
				}
				else if (horizontalDirection == cmhdLeft)
				{
					if (canMoveLeftFalling())
					{
						falling.moveHorizontal(-1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
					}
				}

			}

			if (!falling.getVerticalTransition().isInProgress())
			{
				if (verticalDirection == cmvdDown)
				{
					if (canMoveDownFalling())
					{
						falling.moveVertical(1, Transition::ppfArctangent, FALLING_DOWN_LONGITUDE);
					}
					else
					{
						freezeFalling();
						collectLinesToFire();
					}
				}
				else if (verticalDirection == cmvdDownFast)
				{
					if (canMoveDownFalling())
					{
						falling.moveVertical(1, Transition::ppfLinear, FALLING_DOWN_FAST_LONGITUDE);
					}
				}
			}

			if (!falling.getRotateTransition().isInProgress())
			{
				if (rotationDirection == cmrdCW)
				{
					if (canRotateFalling(1))
					{
						falling.rotate(1, Transition::ppfArctangent, ROTATION_LONGITUDE);
					}
				}
			}
			break;
		case cmsLinesToFireBlinking:
			if (!this->fallen.getBlinkingTransition().isInProgress())
			{
				removeFiredAwayLines();
				state = cmsLinesFiring;
			}

			break;
		case cmsLinesFiring:
			if (!field.anyTransitionsInProgress())
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
			}
			break;

		case cmsGameOver:
			// Doing nothing
			break;
		}

		turnOff(cmcMoveDown);
	}

	sf::Color generateBlockcolor()
	{
		int k = 4;

		float r = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float g = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float b = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;

		return sf::Color(255 * r, 255 * g, 255 * b);
	}

	bool CubesMechanic::createTBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty() &&
		    fallen.cubeAt(6, 2).empty())
		{
			falling.getCubes().push_back(Cube(5, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(7, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 1, Cube::rctCenter);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createJBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(6, 3).empty() &&
		    fallen.cubeAt(5, 3).empty())
		{
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 3, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(5, 3, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 3, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createLBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(5, 3).empty() &&
		    fallen.cubeAt(6, 3).empty())
		{
			falling.getCubes().push_back(Cube(5, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(5, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(5, 3, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 3, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 3, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createIBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(4, 1).empty() &&
		    fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty())
		{
			falling.getCubes().push_back(Cube(4, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(5, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(7, 1, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 1, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createZBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(7, 2).empty())
		{
			falling.getCubes().push_back(Cube(5, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(7, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(7, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createSBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty())
		{
			falling.getCubes().push_back(Cube(5, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(7, 1, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createOBlock()
	{
		sf::Color gen = generateBlockcolor();

		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(6, 2).empty())
		{
			falling.getCubes().push_back(Cube(5, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 1, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(5, 2, Cube::mtPlaying, gen));
			falling.getCubes().push_back(Cube(6, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CubesMechanic::createNewBlock()
	{
		int r = rand() * 7 / RAND_MAX;
		switch (r)
		{
		case 0:
			return createOBlock();
		case 1:
			return createSBlock();
		case 2:
			return createLBlock();
		case 3:
			return createJBlock();
		case 4:
			return createIBlock();
		case 5:
			return createTBlock();
		case 6:
			return createSBlock();
		case 7:
			return createZBlock();
		default:
			return false;
		}

		/*Cube c = sfmlcubes::Cube(sf::Color::Red, true);
		c.slidingX = -0.5;
		c.slidingY = -0.2;
		c.rotatingAngle = 0.3;
		field.cubeAt(0, 0) = c;
		field.cubeAt(0, 1) = sfmlcubes::Cube(sf::Color::Green, true);
		field.cubeAt(0, 2) = sfmlcubes::Cube(sf::Color::Blue, true);
		field.cubeAt(1, 1) = sfmlcubes::Cube(sf::Color::White, true);
		*/
	}

	void CubesMechanic::freezeFalling()
	{
		for (list<Cube>::iterator iter = falling.getCubes().begin(); iter != falling.getCubes().end(); iter++)
		{
			fallen.getCubes().push_back(*iter);
		}
		falling.getCubes().clear();
	}

	void CubesMechanic::turnOff(CubesMechanicCommand command)
	{
		switch (command)
		{
		case cmcMoveDown:
			if (verticalDirection == cmvdDown)
			{
				verticalDirection = cmvdNone;
			}
			break;
		case cmcMoveDownFast:
			if (verticalDirection == cmvdDownFast)
			{
				verticalDirection = cmvdNone;
			}
			break;
		case cmcMoveLeft:
			if (horizontalDirection == cmhdLeft)
			{
				horizontalDirection = cmhdNone;
			}
			break;
		case cmcMoveRight:
			if (horizontalDirection == cmhdRight)
			{
				horizontalDirection = cmhdNone;
			}
			break;
		case cmcRotateCW:
			if (rotationDirection == cmrdCW)
			{
				rotationDirection = cmrdNone;
			}
			break;
		}
	}

	void CubesMechanic::turnOn(CubesMechanicCommand command)
	{
		switch (command)
		{
		case cmcMoveDown:
			if (verticalDirection == cmvdNone)
			{
				verticalDirection = cmvdDown;
			}
			break;
		case cmcMoveDownFast:
			if (verticalDirection == cmvdNone)
			{
				verticalDirection = cmvdDownFast;
			}
			break;
		case cmcMoveLeft:
			if (horizontalDirection == cmhdNone)
			{
				horizontalDirection = cmhdLeft;
			}
			break;
		case cmcMoveRight:
			if (horizontalDirection == cmhdNone)
			{
				horizontalDirection = cmhdRight;
			}
			break;
		case cmcRotateCW:
			if (rotationDirection == cmrdNone)
			{
				rotationDirection = cmrdCW;
			}
			break;
		}
	}
}
