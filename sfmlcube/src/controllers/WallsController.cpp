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
		WallsController::WallsController(const VelocityController& velocityController, int width, int height, int visibleFrame) :
				velocityController(velocityController),
				wallsKinematics(*this), backgroundDealer(width - 2), state(sIdle), width(width), height(height), visibleFrame(visibleFrame), wallColor(sf::Color(96, 96, 96))
		{
			for (int i = 0; i < width; i++)
			{
				walls.addCube(Cube(i, height - 1, Cube::mtWall, wallColor));
			}

			walls.addCube(Cube(0, -1, Cube::mtVoid, wallColor));
			walls.addCube(Cube(width - 1, -1, Cube::mtVoid, wallColor));

			for (int j = -visibleFrame; j < height; j++)
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

		void WallsController::addTopBricks(int count)
		{
			for (int j = - visibleFrame; j >= -count - visibleFrame; j--)
			{
				walls.addCube(Cube(0, j, Cube::mtWall, wallColor));
				walls.addCube(Cube(width - 1, j, Cube::mtWall, wallColor));
			}
		}

		void WallsController::addRowsFromDealer(int count)
		{
			for (int j = 0; j >= -count; j--)
			{
				vector<BackgroundDealer::CellType> newRow = backgroundDealer.dealRow();
				for (int i = 0; i < newRow.size(); i++)
				{
					switch (newRow[i])
					{
					case BackgroundDealer::ctEmpty:
						// add nothing
						break;
					case BackgroundDealer::ctWall:
						// add wall
						walls.addCube(Cube(i + 1, j, Cube::mtWall, wallColor));
						break;
					default:
						Logger::DEFAULT.logWarning("Strange case here...");
						break;
					}
				}
			}
		}

		void WallsController::startFalling(int count)
		{
			// Here we should emulate endless walls,
			// so adding the new bricks to the top
			addTopBricks(count);

			addRowsFromDealer(count);

			// removing the invisible bricks which we will never see again
			walls.removeAllBelow(height + visibleFrame);

			state = sMovingDown;
			wallsKinematics.moveVertical(count, Transition::ppfParabolic, velocityController.getFallingDownFiredLongitude());
			Logger::DEFAULT.logInfo("down");
		}

		WallsController::~WallsController()
		{
		}
	}
}
