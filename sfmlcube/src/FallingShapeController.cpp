/*
 * FallingShapeController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include "FallingShapeController.h"

namespace sfmlcubes
{
	float FallingShapeController::ROTATION_LONGITUDE = 0.25;
	float FallingShapeController::FALLING_DOWN_LONGITUDE = 0.1;
	float FallingShapeController::FALLING_DOWN_FAST_LONGITUDE = 0.05;
	float FallingShapeController::HORIZONTAL_MOVING_LONGITUDE = 0.08;

	void FallingShapeController::updateObstacles()
	{
		fallingDynamics.clearObstacles();
		fallingDynamics.addObstacle(wallsController.getWalls());
		fallingDynamics.addObstacle(fallenController.getFallen());
	}


	FallingShapeController::FallingShapeController(WallsController& wallsController, FallenController& fallenController) :
		state(fscsLanded),
		wallsController(wallsController),
		fallenController(fallenController)
	{
		fallingKinematics.setShape(falling);
		fallingDynamics.setShape(falling);

		createNewBlock();
	}

	void FallingShapeController::processTimeStep(float dt)
	{
		fallingKinematics.advanceStep(dt);

		if (!fallingKinematics.getHorizontalTransition().isInProgress())
		{
			if (movingRight)
			{
				if (fallingDynamics.canMoveRight())
				{
					fallingKinematics.moveHorizontal(1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
				}
			}
			else if (movingLeft)
			{
				if (fallingDynamics.canMoveLeft())
				{
					fallingKinematics.moveHorizontal(-1, Transition::ppfLinear, HORIZONTAL_MOVING_LONGITUDE);
				}
			}

		}

		if (!fallingKinematics.getVerticalTransition().isInProgress())
		{
			bool canFallDown = false;
			if (fallDownPending)
			{
				if (fallingDynamics.canMoveDown())
				{
					fallingKinematics.moveVertical(1, Transition::ppfLinear, FALLING_DOWN_FAST_LONGITUDE);
					canFallDown = true;
				}
				fallDownPending = false;
			}
			else if (fastFalling)
			{
				if (fallingDynamics.canMoveDown())
				{
					fallingKinematics.moveVertical(1, Transition::ppfArctangent, FALLING_DOWN_LONGITUDE);
					canFallDown = true;
				}
			}
		}

		if (!fallingKinematics.getRotateTransition().isInProgress())
		{
			if (rotatingCW)
			{
				if (fallingDynamics.canRotate(1))
				{
					fallingKinematics.rotate(1, Transition::ppfArctangent, ROTATION_LONGITUDE);
				}
			}
		}

	}

	void FallingShapeController::fallDown()
	{
		fallDownPending = true;
	}
	void FallingShapeController::turnOnFastFalling()
	{
		fastFalling = true;
	}
	void FallingShapeController::turnOnRight()
	{
		movingRight = true;
	}
	void FallingShapeController::turnOnLeft()
	{
		movingLeft = true;
	}
	void FallingShapeController::turnOnRotateCW()
	{
		rotatingCW = true;
	}
	void FallingShapeController::turnOffFastFalling()
	{
		fastFalling = false;
	}
	void FallingShapeController::turnOffRight()
	{
		movingRight = false;
	}
	void FallingShapeController::turnOffLeft()
	{
		movingLeft = false;
	}
	void FallingShapeController::turnOffRotateCW()
	{
		rotatingCW = false;
	}


	sf::Color generateBlockcolor()
	{
		int k = 4;

		float r = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float g = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;
		float b = 0.3 + 0.6 * (float)((int)rand() / (RAND_MAX / k)) / k;

		return sf::Color(255 * r, 255 * g, 255 * b);
	}

	bool FallingShapeController::createTBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty() &&
		    fallen.cubeAt(6, 2).empty())
		{
			falling.addCube(Cube(5, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(7, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 1, Cube::rctCenter);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createJBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(6, 3).empty() &&
		    fallen.cubeAt(5, 3).empty())
		{
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 3, Cube::mtPlaying, gen));
			falling.addCube(Cube(5, 3, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 3, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createLBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(5, 3).empty() &&
		    fallen.cubeAt(6, 3).empty())
		{
			falling.addCube(Cube(5, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(5, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(5, 3, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 3, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 3, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createIBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(4, 1).empty() &&
		    fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty())
		{
			falling.addCube(Cube(4, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(5, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(7, 1, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 1, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createZBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(7, 2).empty())
		{
			falling.addCube(Cube(5, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(7, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(7, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createSBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(6, 2).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(7, 1).empty())
		{
			falling.addCube(Cube(5, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(7, 1, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createOBlock(const sf::Color& gen, const Shape& fallen)
	{
		if (fallen.cubeAt(5, 1).empty() &&
		    fallen.cubeAt(6, 1).empty() &&
		    fallen.cubeAt(5, 2).empty() &&
		    fallen.cubeAt(6, 2).empty())
		{
			falling.addCube(Cube(5, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 1, Cube::mtPlaying, gen));
			falling.addCube(Cube(5, 2, Cube::mtPlaying, gen));
			falling.addCube(Cube(6, 2, Cube::mtPlaying, gen));

			falling.setRotatingCenter(6, 2, Cube::rctCorner);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool FallingShapeController::createNewBlock()
	{
		sf::Color gen = generateBlockcolor();
		const Shape& fallen = fallenController.getFallen();

		int r = rand() * 7 / RAND_MAX;
		switch (r)
		{
		case 0:
			return createOBlock(gen, fallen);
		case 1:
			return createSBlock(gen, fallen);
		case 2:
			return createLBlock(gen, fallen);
		case 3:
			return createJBlock(gen, fallen);
		case 4:
			return createIBlock(gen, fallen);
		case 5:
			return createTBlock(gen, fallen);
		case 6:
			return createSBlock(gen, fallen);
		case 7:
			return createZBlock(gen, fallen);
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


	FallingShapeController::~FallingShapeController()
	{
	}

}
