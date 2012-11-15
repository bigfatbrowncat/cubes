/*
 * CubesMechanic.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#include <math.h>

#include "CubesMechanic.h"

namespace sfmlcubes
{
	float CubesMechanic::FALLING_DOWN_LONGITUDE = 0.3;
	float CubesMechanic::HORIZONTAL_MOVING_LONGITUDE = 0.2;

	CubesMechanic::CubesMechanic(int width, int height): field(width, height) {	}
	CubesMechanic::~CubesMechanic() { }

	bool CubesMechanic::cubeIsEmptyOrFreeAt(int i, int j)
	{
		return field.cubeAt(i, j).empty || field.cubeAt(i, j).freeMoving;
	}

	bool CubesMechanic::canMoveDown()
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				// Checking if we are on the floor already
				if (j == field.getHeight() - 1) return false;

				// Checking the cube under our
				if (!cubeIsEmptyOrFreeAt(i, j + 1)) return false;

				// Check if the cube is moved horizontally
				if (horizontalMovingDirection == cmhdRight && i < field.getWidth() - 1)
				{
					if (!cubeIsEmptyOrFreeAt(i + 1, j + 1)) return false;
				}
				if (horizontalMovingDirection == cmhdLeft && i > 0)
				{
					if (!cubeIsEmptyOrFreeAt(i - 1, j + 1)) return false;
				}
			}
		}
		return true;
	}

	bool CubesMechanic::canMoveLeft()
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				// Checking if we are near the left wall already
				if (i == 0) return false;

				// Checking the cube on the left
				if (!cubeIsEmptyOrFreeAt(i - 1, j)) return false;

				// Check if the cube is moved vertically
				if (verticalMovingDirection == cmvdDown && j < field.getHeight() - 1)
				{
					if (!cubeIsEmptyOrFreeAt(i - 1, j + 1)) return false;
				}
				if (verticalMovingDirection == cmvdUp && j > 0)
				{
					if (!cubeIsEmptyOrFreeAt(i - 1, j - 1)) return false;
				}
			}
		}
		return true;
	}

	bool CubesMechanic::canMoveRight()
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				// Checking if we are near the right wall already
				if (i == field.getWidth() - 1) return false;

				// Checking the cube on the right
				if (!cubeIsEmptyOrFreeAt(i + 1, j)) return false;

				// Check if the cube is moved vertically
				if (verticalMovingDirection == cmvdDown && j < field.getHeight() - 1)
				{
					if (!cubeIsEmptyOrFreeAt(i + 1, j + 1)) return false;
				}
				if (verticalMovingDirection == cmvdUp && j > 0)
				{
					if (!cubeIsEmptyOrFreeAt(i + 1, j - 1)) return false;
				}
			}
		}
		return true;
	}

	void CubesMechanic::moveDown()
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = field.getHeight() - 2; j >= 0; j--)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i, j + 1) = field.cubeAt(i, j);
				field.cubeAt(i, j).empty = true;
			}
		}
	}

	void CubesMechanic::moveRight()
	{
		for (int i = field.getWidth() - 2; i >= 0; i--)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i + 1, j) = field.cubeAt(i, j);
				field.cubeAt(i, j).empty = true;
			}
		}
	}

	void CubesMechanic::moveLeft()
	{
		for (int i = 1; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i - 1, j) = field.cubeAt(i, j);
				field.cubeAt(i, j).empty = true;
			}
		}
	}

	void CubesMechanic::cleanFrees()
	{
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				field.cubeAt(i, j).freeMoving = false;
			}
		}
	}

	CubesMechanicIssueResponse CubesMechanic::issueMovingDown()
	{
		if (!canMoveDown())
		{
			return cmirCantBecauseObstacle;
		}
		else if (verticalMovingDirection == cmvdDown)
		{
			return cmirAlreadyInProgress;
		}
		else
		{
			verticalMovingDirection = cmvdDown;
			verticalMovingPhase = 0;
			return cmirSuccess;
		}
	}

	CubesMechanicIssueResponse CubesMechanic::issueMovingRight()
	{
		if (!canMoveRight() || horizontalMovingDirection == cmhdLeft)
		{
			return cmirCantBecauseObstacle;
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

	CubesMechanicIssueResponse CubesMechanic::issueMovingLeft()
	{
		if (!canMoveLeft() || horizontalMovingDirection == cmhdRight)
		{
			return cmirCantBecauseObstacle;
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

	void CubesMechanic::processTimeStep(float dt)
	{
		float slidingX = 0, slidingY = 0;

		// Vertical movement
		if (verticalMovingDirection == cmvdDown)
		{
			verticalMovingPhase += dt / FALLING_DOWN_LONGITUDE;

			if (verticalMovingPhase < 1)
			{
				float slope = 1.5f;
				slidingY = atan(slope * (verticalMovingPhase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;
			}
			else
			{
				verticalMovingPhase = 0;
				moveDown();
				slidingY = 0;
				verticalMovingDirection = cmvdNone;;
			}
		}

		// Horizontal movement
		if (horizontalMovingDirection == cmhdRight)
		{
			horizontalMovingPhase += dt / HORIZONTAL_MOVING_LONGITUDE;

			if (horizontalMovingPhase < 1)
			{
				slidingX = horizontalMovingPhase;
			}
			else
			{
				horizontalMovingPhase = 0;
				moveRight();
				slidingX = 0;
				horizontalMovingDirection = cmhdNone;
			}
		}
		else if (horizontalMovingDirection == cmhdLeft)
		{
			horizontalMovingPhase += dt / HORIZONTAL_MOVING_LONGITUDE;

			if (horizontalMovingPhase < 1)
			{
				slidingX = -horizontalMovingPhase;
			}
			else
			{
				horizontalMovingPhase = 0;
				moveLeft();
				slidingX = 0;
				horizontalMovingDirection = cmhdNone;
			}
		}

		setSliding(slidingX, slidingY);
	}

	void CubesMechanic::createNewBlock()
	{
		/*Cube c = sfmlcubes::Cube(sf::Color::Red, true);
		c.slidingX = -0.5;
		c.slidingY = -0.2;
		c.rotatingAngle = 0.3;
		field.cubeAt(0, 0) = c;
		field.cubeAt(0, 1) = sfmlcubes::Cube(sf::Color::Green, true);
		field.cubeAt(0, 2) = sfmlcubes::Cube(sf::Color::Blue, true);
		field.cubeAt(1, 1) = sfmlcubes::Cube(sf::Color::White, true);
		*/

		sf::Color gray = sf::Color(192, 192, 192);
		field.cubeAt(0, 0) = sfmlcubes::Cube(gray, true);
		field.cubeAt(0, 1) = sfmlcubes::Cube(gray, true);
		field.cubeAt(0, 2) = sfmlcubes::Cube(gray, true);
		field.cubeAt(1, 1) = sfmlcubes::Cube(gray, true);
	}

	void CubesMechanic::test_createBlueCube()
	{
		field.cubeAt(0, 7) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 2) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 3) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 4) = sfmlcubes::Cube(sf::Color::Blue, false);

	}
}
