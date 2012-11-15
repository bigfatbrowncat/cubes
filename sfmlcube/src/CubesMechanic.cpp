/*
 * CubesMechanic.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#include <math.h>
#include <stdio.h>

#include "CubesMechanic.h"

namespace sfmlcubes
{
	float CubesMechanic::ROTATION_LONGITUDE = 0.3;
	float CubesMechanic::FALLING_DOWN_LONGITUDE = 0.3;
	float CubesMechanic::FALLING_DOWN_FAST_LONGITUDE = 0.1;
	float CubesMechanic::HORIZONTAL_MOVING_LONGITUDE = 0.2;

	CubesMechanic::CubesMechanic(int width, int height):
			field(width, height),

			verticalMovingDirection(cmvdNone),
			verticalMovingPhase(0),

			horizontalMovingDirection(cmhdNone),
			horizontalMovingPhase(0)
	{

	}

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
				if ((verticalMovingDirection == cmvdDown || verticalMovingDirection == cmvdDownFast) && j < field.getHeight() - 1)
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
				if ((verticalMovingDirection == cmvdDown || verticalMovingDirection == cmvdDownFast) && j < field.getHeight() - 1)
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

	CubesMechanic::RotationData CubesMechanic::findCenter()
	{
		// Calculating the center of the falling cubes
		float centerX = 0, centerY = 0;
		int k = 0;
		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				centerX += i + 0.5;
				centerY += j + 0.5;
				k ++;
			}
		}
		centerX /= k; centerY /= k;
		int dblX = round(2 * centerX);
		int dblY = round(2 * centerY);

		int rotationCenterX, rotationCenterY;
		CubeRotatingCenterType crct;

		if (dblX % 2 == 0)
		{
			crct = crctCenterOfCube;
			rotationCenterX = dblX / 2;
			rotationCenterY = dblY / 2;
		}
		else
		{
			crct = crctCornerOfCube;
			rotationCenterX = (dblX + 1) / 2;
			rotationCenterY = (dblY + 1) / 2;

		}

		// Finding the radius of the falling cubes
		float R = 0;

		float cx = rotationCenterX - (crct == crctCornerOfCube ? 0.5 : 0);
		float cy = rotationCenterY - (crct == crctCornerOfCube ? 0.5 : 0);

		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				double r = sqrt((cx - i)*(cx - i) + (cy - j)*(cy - j));
				if (R < r) R = r;
			}
		}
		RotationData res;

		res.R = round(ceil(R));
		if (crct == crctCenterOfCube) res.R++;
		printf("R = %d\n", res.R);
		fflush(stdout);

		res.crct = crct;
		res.x = rotationCenterX;
		res.y = rotationCenterY;
		return res;
	}

	bool CubesMechanic::canRotate()
	{
		RotationData rd = findCenter();

		//float cx = rd.x - (rd.crct == crctCornerOfCube ? 0.5 : 0);
		//float cy = rd.y - (rd.crct == crctCornerOfCube ? 0.5 : 0);

		if (rd.crct == crctCenterOfCube)
		{
			for (int i = rd.x - rd.R + 1; i < rd.x + rd.R; i++)
			for (int j = rd.y - rd.R + 1; j < rd.y + rd.R; j++)
			{
				if (i < 0 || j < 0 || i >= field.getWidth() || j >= field.getHeight())
				{
					// We are out of the field
					return false;
				}
				if (!cubeIsEmptyOrFreeAt(i, j))
				{
					// Some obstacle found
					return false;
				}
			}
		}
		else if (rd.crct == crctCornerOfCube)
		{
			for (int i = rd.x - rd.R; i < rd.x + rd.R; i++)
			for (int j = rd.y - rd.R; j < rd.y + rd.R; j++)
			{
				if (i < 0 || j < 0 || i >= field.getWidth() || j >= field.getHeight())
				{
					// We are out of the field
					return false;
				}
				if (!cubeIsEmptyOrFreeAt(i, j))
				{
					// Some obstacle found
					return false;
				}
			}
		}
		else { printf("[LOG] Error: strange case!"); }

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

	void CubesMechanic::rotate(int angle)
	{
		RotationData rd = findCenter();

		if (rd.crct == crctCenterOfCube)
		{
			// Searching for anything in our radius
			for (int i = rd.x - rd.R + 1; i <= rd.x; i++)
			for (int j = rd.y - rd.R + 1; j < rd.y; j++)
			{
				{
					// Calculating 3 images for our position
					int ik[4], jk[4];
					int i0 = rd.x, j0 = rd.y;

					// Making the 90 degrees rotating group
					ik[0] = i;
					jk[0] = j;
					for (int k = 1; k < 4; k++)
					{
						ik[k] = i0 - jk[k - 1] + j0;
						jk[k] = j0 + ik[k - 1] - i0;
					}

					// Making the group array
					Cube group[4];
					for (int k = 0; k < 4; k++)
					{
						group[k] = field.cubeAt(ik[k], jk[k]);
					}

					// Rotating the group
					for (int k = 0; k < 4; k++)
					{
						int kold = (k + 4 - angle) % 4;

						field.cubeAt(ik[k], jk[k]) = group[kold];
					}
				}
			}
		}
		else if (rd.crct == crctCornerOfCube)
		{
			// Searching for anything in our radius
			for (int i = rd.x - rd.R; i < rd.x; i++)
			for (int j = rd.y - rd.R; j < rd.y; j++)
			{
				/*if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)*/
				{
					// Calculating 3 images for our position
					int ik[4], jk[4];
					int i0 = rd.x, j0 = rd.y;

					// Making the 90 degrees rotating group
					ik[0] = i;
					jk[0] = j;
					for (int k = 1; k < 4; k++)
					{
						ik[k] = i0 - jk[k - 1] + j0 - 1;
						jk[k] = j0 + ik[k - 1] - i0;
					}

					// Making the group array
					Cube group[4];
					for (int k = 0; k < 4; k++)
					{
						group[k] = field.cubeAt(ik[k], jk[k]);
					}

					// Rotating the group
					for (int k = 0; k < 4; k++)
					{
						int kold = (k + 4 - angle) % 4;

						field.cubeAt(ik[k], jk[k]) = group[kold];
					}
				}
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

	CubesMechanicIssueResponse CubesMechanic::issueMovingDown(bool fast)
	{
		if (!canMoveDown())
		{
			return cmirCantBecauseObstacle;
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

	CubesMechanicIssueResponse CubesMechanic::issueRotatingCW()
	{
		if (!canRotate() || rotationDirection == cmrdCCW)
		{
			return cmirCantBecauseObstacle;
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


	void CubesMechanic::processTimeStep(float dt)
	{
		// ** Rotation **
		RotationData rd = findCenter();

		float rotationAngle = 0;

		if (rotationDirection == cmrdCW)
		{
			rotationPhase += dt / ROTATION_LONGITUDE;

			if (rotationPhase < 1)
			{
				float slope = 1.5f;
				rotationAngle = atan(slope * (rotationPhase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;
			}
			else
			{
				rotationPhase = 0;
				rotate(1);
				rotationAngle = 0;
				rotationDirection = cmrdNone;
			}
		}

		setRotation(rd.x, rd.y, rd.crct, rotationAngle);

		// ** Sliding **

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
				verticalMovingDirection = cmvdNone;
			}
		}
		else if (verticalMovingDirection == cmvdDownFast)
		{
			verticalMovingPhase += dt / FALLING_DOWN_FAST_LONGITUDE;

			if (verticalMovingPhase < 1)
			{
				slidingY = verticalMovingPhase;
			}
			else
			{
				verticalMovingPhase = 0;
				moveDown();
				slidingY = 0;
				verticalMovingDirection = cmvdNone;
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
		field.cubeAt(6, 0) = sfmlcubes::Cube(gray, true);
		field.cubeAt(6, 1) = sfmlcubes::Cube(gray, true);
		field.cubeAt(6, 2) = sfmlcubes::Cube(gray, true);
		field.cubeAt(7, 1) = sfmlcubes::Cube(gray, true);
	}

	void CubesMechanic::test_createBlueCube()
	{
		/*field.cubeAt(0, 7) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 2) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 3) = sfmlcubes::Cube(sf::Color::Blue, false);
		field.cubeAt(2, 4) = sfmlcubes::Cube(sf::Color::Blue, false);*/

	}
}
