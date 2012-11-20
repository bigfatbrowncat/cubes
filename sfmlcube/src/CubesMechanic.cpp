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
	float CubesMechanic::ROTATION_LONGITUDE = 0.25;
	float CubesMechanic::FALLING_DOWN_LONGITUDE = 0.1;
	float CubesMechanic::FALLING_DOWN_FAST_LONGITUDE = 0.05;
	float CubesMechanic::HORIZONTAL_MOVING_LONGITUDE = 0.08;
	float CubesMechanic::LINES_FIRING_LONGITUDE = 1;
	float CubesMechanic::LINES_FIRING_BLINKING_PART = 0.8;

	CubesMechanic::CubesMechanic(int width, int height):
			field(width, height),
			background(field),
			falling(field),
			fallen(field),

			verticalMovingDirection(cmvdNone),
			horizontalMovingDirection(cmhdNone)

	{
		field.getCubesGroups().push_back(&background);
		field.getCubesGroups().push_back(&fallen);
		field.getCubesGroups().push_back(&falling);

		sf::Color wallColor = sf::Color(32, 32, 32);

		for (int i = 0; i < field.getWidth(); i++)
		{
			background.getCubes().push_back(Cube(cmtWall, i, field.getHeight() - 1, wallColor));
		}
		for (int j = 2; j < field.getHeight(); j++)
		{
			background.getCubes().push_back(Cube(cmtWall, 0, j, wallColor));
			background.getCubes().push_back(Cube(cmtWall, field.getWidth() - 1, j, wallColor));
		}
	}

	CubesMechanic::~CubesMechanic() { }

	CubesMechanicIssueResponse CubesMechanic::executeNextOrder()
	{
		if (beforeOrderIssuingNotifier != NULL)
		{
			(*beforeOrderIssuingNotifier)();
		}

		if (ordersQueue.size() == 0)
		{
			return cmirNothingToIssue;
		}
		else
		{
			CubesMechanicOrder nextOrder = ordersQueue.back();
			ordersQueue.pop_back();
			CubesMechanicIssueResponse resp = cmirNothingToIssue;
			switch (nextOrder)
			{
			case cmoMoveDown:
				falling.moveDown();
				break;
			case cmoMoveDownFast:
				//resp = startMovingDownTransition(true);
				break;
			case cmoMoveLeft:
				falling.moveLeft();
				break;
			case cmoMoveRight:
				falling.moveRight();
				break;
			case cmoRotateCW:
				falling.rotateCW(1);
				break;
			case cmoFireLines:
				//resp = startFiringLinesTransition();
				break;
			}

/*			if (orderIssuedNotifier != NULL)
			{
				(*orderIssuedNotifier)(nextOrder, resp);
			}*/
			return resp;
		}
	}

/*	bool CubesMechanic::canMoveDown()
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

	float CubesMechanic::calculateRadius(int rotationCenterX, int rotationCenterY, CubeRotatingCenterType crct)
	{
		// Finding the radius of the falling cubes
		float R = 0;

		float cx = rotationCenterX;// - (crct == crctCenterOfCube ? 0.5 : 0);
		float cy = rotationCenterY;// - (crct == crctCenterOfCube ? 0.5 : 0);

		for (int i = 0; i < field.getWidth(); i++)
		for (int j = 0; j < field.getHeight(); j++)
		{
			if (!field.cubeAt(i, j).empty && field.cubeAt(i, j).freeMoving)
			{
				double r = i <= cx ? cx - i : i + 1 - cx;  //sqrt((cx - i)*(cx - i) + (cy - j)*(cy - j));
				if (R < r) R = r;
				r = j <= cy ? cy - j : j + 1 - cy;
				if (R < r) R = r;
			}
		}

		return R;
	}

	bool CubesMechanic::canRotate()
	{
		float R = calculateRadius(fallingCenterX, fallingCenterY, fallingCRCT);

		if (fallingCRCT == crctCenterOfCube)
		{
			for (int i = fallingCenterX - R + 1; i < fallingCenterX + R; i++)
			for (int j = fallingCenterY - R + 1; j < fallingCenterY + R; j++)
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
		else if (fallingCRCT == crctCornerOfCube)
		{
			for (int i = fallingCenterX - R; i < fallingCenterX + R; i++)
			for (int j = fallingCenterY - R; j < fallingCenterY + R; j++)
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

	bool CubesMechanic::canFireLines()
	{
		linesToFire.clear();
		for (int j = 0; j < field.getHeight(); j++)
		{
			bool thisRowIsFull = true;
			for (int i = 0; i < field.getWidth(); i++)
			{
				if (field.cubeAt(i, j).empty) thisRowIsFull = false;
			}
			if (thisRowIsFull)
			{
				linesToFire.push_back(j);
			}
		}
		return linesToFire.size() > 0;
	}


	void CubesMechanic::fireLines()
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
	}


	void CubesMechanic::rotate(CubesMechanicDiscreteAngle angle)
	{
		float R = calculateRadius(fallingCenterX, fallingCenterY, fallingCRCT);

		if (fallingCRCT == crctCenterOfCube)
		{
			// Searching for anything in our radius
			for (int i = fallingCenterX - R + 1; i <= fallingCenterX; i++)
			for (int j = fallingCenterY - R + 1; j < fallingCenterY; j++)
			{
				{
					// Calculating 3 images for our position
					int ik[4], jk[4];
					int i0 = fallingCenterX, j0 = fallingCenterY;

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
						if (ik[k] >= 0 && ik[k] < field.getWidth() && jk[k] >= 0 && jk[k] < field.getHeight())
							group[k] = field.cubeAt(ik[k], jk[k]);
						else
							group[k] = Cube::EMPTY;
					}

					// Rotating the group
					for (int k = 0; k < 4; k++)
					{
						int kold = (k + 4 - angle) % 4;

						if (ik[k] >= 0 && ik[k] < field.getWidth() && jk[k] >= 0 && jk[k] < field.getHeight())
							field.cubeAt(ik[k], jk[k]) = group[kold];
					}
				}
			}
		}
		else if (fallingCRCT == crctCornerOfCube)
		{
			// Searching for anything in our radius
			for (int i = fallingCenterX - R; i < fallingCenterX; i++)
			for (int j = fallingCenterY - R; j < fallingCenterY; j++)
			{

				{
					// Calculating 3 images for our position
					int ik[4], jk[4];
					int i0 = fallingCenterX, j0 = fallingCenterY;

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
						if (ik[k] >= 0 && ik[k] < field.getWidth() && jk[k] >= 0 && jk[k] < field.getHeight())
							group[k] = field.cubeAt(ik[k], jk[k]);
						else
							group[k] = Cube::EMPTY;
					}

					// Rotating the group
					for (int k = 0; k < 4; k++)
					{
						int kold = (k + 4 - angle) % 4;

						if (ik[k] >= 0 && ik[k] < field.getWidth() && jk[k] >= 0 && jk[k] < field.getHeight())
							field.cubeAt(ik[k], jk[k]) = group[kold];
					}
				}
			}
		}
		sumRotationValue = (CubesMechanicDiscreteAngle)((sumRotationValue + 1) % 4);
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
*/
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
		if (!canFireLines())
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

/*		if (horizontalMovingDirection != cmhdNone &&
		    horizontalTransition.advanceStep(dt / HORIZONTAL_MOVING_LONGITUDE) == Transition::asrFinished)
		{
			horizontalTransition.reset();
			switch (horizontalMovingDirection)
			{
			case cmhdRight:
				moveRight();
				break;
			case cmhdLeft:
				moveLeft();
				break;
			default:
				Logger::DEFAULT.logError("Strange case of horizontalMovingDirection");
				break;
			}

		}

		if (verticalMovingDirection != cmvdNone &&
		    verticalTransition.advanceStep(dt / FALLING_DOWN_LONGITUDE) == Transition::asrFinished)
		{
			verticalTransition.reset();
			switch (verticalMovingDirection)
			{
			case cmvdDown:
				moveDown();
				break;
			default:
				Logger::DEFAULT.logError("Strange case of horizontalMovingDirection");
				break;
			}
		}

		if (rotationDirection != cmrdNone &&
		    rotateTransition.advanceStep(dt / ROTATION_LONGITUDE) == Transition::asrFinished)
		{
			rotateTransition.reset();
			switch (rotationDirection)
			{
			case cmrdCW:
				rotate(cmda90CW);
				break;
			default:
				Logger::DEFAULT.logError("Strange case of horizontalMovingDirection");
				break;
			}
		}

		if (linesAreFiring)
		{
			linesFiringPhase += dt / LINES_FIRING_LONGITUDE;
			if (linesFiringPhase < LINES_FIRING_BLINKING_PART)
			{
				float blinkingPhase = (linesFiringPhase / LINES_FIRING_BLINKING_PART) * 3.5;
				setFiringLinesAlpha(abs(sin(3.14159 * blinkingPhase)));
			}
			else if (linesFiringPhase < 1)
			{
				setFiringLinesAlpha(0);
				float slidingPhase = (linesFiringPhase - LINES_FIRING_BLINKING_PART) / (1.0 - LINES_FIRING_BLINKING_PART);
				setFiringLinesSliding(slidingPhase * slidingPhase);
			}
			else
			{
				linesFiringPhase = 0;
				setFiringLinesSliding(0);
				fireLines();
				linesAreFiring = false;
				if (transitionFinishedNotifier != NULL)
				{
					(*transitionFinishedNotifier)(cmoFireLines);
				}
				executeNextOrder();
			}

		}
		else
		{
			executeNextOrder();
		}
		*/
	}

	sf::Color generateBlockcolor()
	{
		int k = 4;

		float r = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float g = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float b = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
/*		float norm = sqrt(r*r + g*g + b*b);
		r /= norm;
		g /= norm;
		b /= norm;*/

		return sf::Color(255 * r, 255 * g, 255 * b);
	}

	bool CubesMechanic::createTBlock()
	{
		sf::Color gen = generateBlockcolor();

		falling.getCubes().push_back(Cube(cmtPlaying, 5, 1, gen));
		falling.getCubes().push_back(Cube(cmtPlaying, 6, 1, gen));
		falling.getCubes().push_back(Cube(cmtPlaying, 7, 1, gen));
		falling.getCubes().push_back(Cube(cmtPlaying, 6, 2, gen));

		falling.setRotatingCenter(6, 1, crctCenterOfCube);

		return true;
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

	void CubesMechanic::issueOrder(CubesMechanicOrder order)
	{
		ordersQueue.push_front(order);
		ordersQueue.unique();
		executeNextOrder();			// Temporary
	}

	void CubesMechanic::issueHighPriorityOrder(CubesMechanicOrder order)
	{
		ordersQueue.push_back(order);
		ordersQueue.unique();
	}

}
