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
#include "Transition.h"
#include "CubesField.h"

using namespace std;

namespace sfmlcubes
{
	CubesMechanic::CubesMechanic(int width, int height):
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

		sf::Color wallColor = sf::Color(32, 32, 32);

		for (int i = 0; i < field.getWidth(); i++)
		{
			walls.getCubes().push_back(Cube(cmtWall, i, field.getHeight() - 1, wallColor));
		}
		for (int j = 2; j < field.getHeight(); j++)
		{
			walls.getCubes().push_back(Cube(cmtWall, 0, j, wallColor));
			walls.getCubes().push_back(Cube(cmtWall, field.getWidth() - 1, j, wallColor));
		}
	}

	CubesMechanic::~CubesMechanic() { }

	bool CubesMechanic::areAnyCollisions()
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
		falling.moveDownNoTransition();
		bool res = !areAnyCollisions();
		falling.moveUpNoTransition();

		return res;
	}

	bool CubesMechanic::canMoveLeftFalling()
	{
		falling.moveLeftNoTransition();
		bool res = !areAnyCollisions();
		falling.moveRightNoTransition();

		return res;
	}

	bool CubesMechanic::canMoveRightFalling()
	{
		falling.moveRightNoTransition();
		bool res = !areAnyCollisions();
		falling.moveLeftNoTransition();

		return res;
	}

	bool CubesMechanic::canRotateCWFalling(int angle)
	{
		falling.rotateCWNoTransition(angle);
		bool res = !areAnyCollisions();
		falling.rotateCWNoTransition(-angle);

		return res;
	}


	bool CubesMechanic::countLinesToFire()
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


/*	void CubesMechanic::fireLines()
	{
		int count = 0;
		for (int j = field.getHeight() - 1; j >= count; j--)
		{
			// Check if this line is full
			bool thisRowIsFull = true;
			for (int i = 0; i < field.getWidth(); i++)
			{
				if (field.cubeAt(i, j).empty) thisRowIsFull = false;
			}

			if (thisRowIsFull)
			{
				count ++;
			}
			else
			{
				for (int i = 0; i < field.getWidth(); i++)
				{
					field.cubeAt(i, j + count) = field.cubeAt(i, j);
				}
			}
		}
		linesFired += count;
	}*/

/*	CubesMechanicIssueResponse CubesMechanic::startMovingDownTransition(bool fast)
	{
		if (!canMoveDown())
		{
			return cmirFail;
		}
		else if (verticalMovingDirection == cmvdDown || verticalMovingDirection == cmvdDownFast)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			if (fast)
			{
				verticalMovingDirection = cmvdDownFast;
			}
			else
			{
				verticalMovingDirection = cmvdDown;
			}
			verticalMovingPhase = 0;
			return cmirSuccess;
		}
	}

	CubesMechanicIssueResponse CubesMechanic::startMovingRightTransition()
	{
		if (!canMoveRight() || horizontalMovingDirection == cmhdLeft)
		{
			return cmirFail;
		}
		else if (horizontalMovingDirection == cmhdRight)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			horizontalMovingDirection = cmhdRight;
			horizontalMovingPhase = 0;
			return cmirSuccess;
		}
	}

	CubesMechanicIssueResponse CubesMechanic::startMovingLeftTransition()
	{
		if (!canMoveLeft() || horizontalMovingDirection == cmhdRight)
		{
			return cmirFail;
		}
		else if (horizontalMovingDirection == cmhdLeft)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			horizontalMovingDirection = cmhdLeft;
			horizontalMovingPhase = 0;
			return cmirSuccess;
		}
	}

	CubesMechanicIssueResponse CubesMechanic::startRotatingCWTransition()
	{
		if (!canRotate() || rotationDirection == cmrdCCW)
		{
			return cmirFail;
		}
		else if (rotationDirection == cmrdCW)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			rotationDirection = cmrdCW;
			rotationPhase = 0;
			return cmirSuccess;
		}
	}

	CubesMechanicIssueResponse CubesMechanic::startFiringLinesTransition()
	{
		if (!countLinesToFire())
		{
			return cmirFail;
		}
		else if (linesAreFiring)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			linesAreFiring = true;
			linesFiringPhase = 0;
			return cmirSuccess;
		}
	}

	void CubesMechanic::setSliding(float slidingX, float slidingY)
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i, j).slidingX = slidingX;
				field.cubeAt(i, j).slidingY = slidingY;
			}
		}
	}

	void CubesMechanic::setRotation(int centerX, int centerY, CubeRotatingCenterType crct, float angle)
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i, j).rotatingCenterX = centerX;
				field.cubeAt(i, j).rotatingCenterY = centerY;
				field.cubeAt(i, j).rotatingCenterType = crct;
				field.cubeAt(i, j).rotatingAngle = angle;
			}
		}
	}

	void CubesMechanic::setFiringLinesAlpha(float alpha)
	{
		for (list<int>::iterator iter = linesToFire.begin(); iter != linesToFire.end(); iter++)
		{
			int j = *iter;
			for (int i = 0; i < field.getWidth(); i++)
			{
				field.cubeAt(i, j).color.a = alpha * 255;
			}
		}
	}
	void CubesMechanic::setFiringLinesSliding(float phase)
	{
		int count = 0;
		for (int j = field.getHeight() - 1; j >= count; j--)
		{
			// Check if this line is full
			bool thisRowIsFull = true;
			for (int i = 0; i < field.getWidth(); i++)
			{
				if (field.cubeAt(i, j).empty) thisRowIsFull = false;
			}

			if (thisRowIsFull)
			{
				count ++;
			}
			else
			{
				for (int i = 0; i < field.getWidth(); i++)
				{
					field.cubeAt(i, j).slidingY = phase * count;
				}
			}
		}
	}
*/

	void CubesMechanic::processTimeStep(float dt)
	{
		falling.advanceStep(dt);

		// We can move vertically, horizontally and rotate at the same time,
		// so let's check our states and run commands

		if (!falling.getHorizontalTransition().isInProgress())
		{
			if (horizontalDirection == cmhdRight)
			{
				if (canMoveRightFalling())
				{
					falling.moveRight();
				}
			}
			else if (horizontalDirection == cmhdLeft)
			{
				if (canMoveLeftFalling())
				{
					falling.moveLeft();
				}
			}

		}

		if (!falling.getVerticalTransition().isInProgress())
		{
			if (verticalDirection == cmvdDown)
			{
				if (canMoveDownFalling())
				{
					falling.moveDown(false);
				}
			}
			else if (verticalDirection == cmvdDownFast)
			{
				if (canMoveDownFalling())
				{
					falling.moveDown(true);
				}
			}

		}


		if (!falling.getRotateTransition().isInProgress())
		{
			if (rotationDirection == cmrdCW)
			{
				if (canRotateCWFalling(1))
				{
					falling.rotateCW(1);
				}
			}
		}
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
			falling.getCubes().push_back(Cube(cmtPlaying, 5, 1, gen));
			falling.getCubes().push_back(Cube(cmtPlaying, 6, 1, gen));
			falling.getCubes().push_back(Cube(cmtPlaying, 7, 1, gen));
			falling.getCubes().push_back(Cube(cmtPlaying, 6, 2, gen));

			falling.setRotatingCenter(6, 1, crctCenterOfCube);
			return true;
		}
		else
		{
			return false;
		}
	}
/*	bool CubesMechanic::createJBlock()
	{
		if (field.cubeAt(6, 1).empty &&
		    field.cubeAt(6, 2).empty &&
		    field.cubeAt(6, 3).empty &&
		    field.cubeAt(5, 3).empty)
		{
			sf::Color gen = generateBlockcolor();
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 3) = sfmlcubes::Cube(gen, true);
			field.cubeAt(5, 3) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCenterOfCube;
			fallingCenterX = 6;
			fallingCenterY = 2;
			return true;
		}
		else
			return false;
	}
	bool CubesMechanic::createLBlock()
	{
		if (field.cubeAt(6, 1).empty &&
		    field.cubeAt(6, 2).empty &&
		    field.cubeAt(6, 3).empty &&
		    field.cubeAt(7, 3).empty)
		{
			sf::Color gen = sf::Color(192, 192, 192);
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 3) = sfmlcubes::Cube(gen, true);
			field.cubeAt(7, 3) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCenterOfCube;
			fallingCenterX = 6;
			fallingCenterY = 2;
			return true;
		}
		else
			return false;
	}
	bool CubesMechanic::createIBlock()
	{
		if (field.cubeAt(5, 1).empty &&
		    field.cubeAt(6, 1).empty &&
		    field.cubeAt(7, 1).empty &&
		    field.cubeAt(8, 1).empty)
		{
			sf::Color gen = generateBlockcolor();
			field.cubeAt(5, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(7, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(8, 1) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCornerOfCube;
			fallingCenterX = 7;
			fallingCenterY = 1;
			return true;
		}
		else
			return false;
	}
	bool CubesMechanic::createZBlock()
	{
		if (field.cubeAt(5, 1).empty &&
		    field.cubeAt(6, 1).empty &&
		    field.cubeAt(6, 2).empty &&
		    field.cubeAt(7, 2).empty)
		{
			sf::Color gen = generateBlockcolor();
			field.cubeAt(5, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(7, 2) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCornerOfCube;
			fallingCenterX = 7;
			fallingCenterY = 2;
			return true;
		}
		else
			return false;
	}
	bool CubesMechanic::createSBlock()
	{
		if (field.cubeAt(5, 2).empty &&
		    field.cubeAt(6, 2).empty &&
		    field.cubeAt(6, 1).empty &&
		    field.cubeAt(7, 1).empty)
		{
			sf::Color gen = generateBlockcolor();
			field.cubeAt(5, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(7, 1) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCornerOfCube;
			fallingCenterX = 6;
			fallingCenterY = 2;
			return true;
		}
		else
			return false;
	}
	bool CubesMechanic::createOBlock()
	{
		if (field.cubeAt(5, 1).empty &&
		    field.cubeAt(6, 1).empty &&
		    field.cubeAt(5, 2).empty &&
		    field.cubeAt(6, 2).empty)
		{
			sf::Color gen = generateBlockcolor();
			field.cubeAt(5, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 1) = sfmlcubes::Cube(gen, true);
			field.cubeAt(5, 2) = sfmlcubes::Cube(gen, true);
			field.cubeAt(6, 2) = sfmlcubes::Cube(gen, true);

			fallingCRCT = crctCornerOfCube;
			fallingCenterX = 6;
			fallingCenterY = 2;
			return true;
		}
		else
			return false;
	}*/
	bool CubesMechanic::createNewBlock()
	{
		return createTBlock();

		/*int r = rand() * 7 / RAND_MAX;
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
		}*/

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
