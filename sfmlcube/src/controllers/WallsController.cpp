/*
 * WallsController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include <SFML/Graphics/Color.hpp>

#include "../movingcubes/Cube.h"

#include "WallsController.h"
#include "../Logger.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		WallsController::WallsController(const VelocityController& velocityController, int width, int height) :
				velocityController(velocityController),
				wallsKinematics(*this), width(width), height(height), state(sIdle)
		{
			sf::Color wallColor = sf::Color(96, 96, 96);

			for (int i = 0; i < width; i++)
			{
				walls.addCube(Cube(i, height - 1, Cube::mtWall, wallColor));
			}

			walls.addCube(Cube(0, -1, Cube::mtVoid, wallColor));
			walls.addCube(Cube(width - 1, -1, Cube::mtVoid, wallColor));

			for (int j = 0; j < height; j++)
			{
				walls.addCube(Cube(0, j, Cube::mtWall, wallColor));
				walls.addCube(Cube(width - 1, j, Cube::mtWall, wallColor));
			}
		}

		void WallsController::processTimeStep(float dt)
		{
			wallsKinematics.advanceStep(dt);

			switch (state)
			{
			case sIdle:
				// Do nothing, just wait
				break;

			case sMovingDown:

				if (!wallsKinematics.getVerticalTransition().isInProgress())
				{
					Logger::DEFAULT.logInfo("down ok");
					state = sIdle;
				}
				break;
			}
		}

		void WallsController::startMovingDown()
		{
			state = sMovingDown;
			wallsKinematics.moveVertical(1, Transition::ppfParabolic, velocityController.getFallingDownFiredLongitude());
			Logger::DEFAULT.logInfo("down");
		}

		void WallsController::moveDown()
		{
			//walls.moveVerticalNoTransition(1);
			startMovingDown();
		}

		WallsController::~WallsController()
		{
		}
	}
}
