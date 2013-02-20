/*
 * WallsController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include <SFML/Graphics/Color.hpp>

#include "../movingcubes/Cube.h"
#include "../movingcubes/ShapeDynamics.h"
#include "../movingcubes/transitions/ParabolicPhaseProcessingFunction.h"
#include "WallsController.h"
#include "../Logger.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		WallsController::WallsController(const VelocityController& velocityController, int width, int height, int visibleFrame) :
				velocityController(velocityController),
				wallsKinematics(walls), state(sIdle), width(width), height(height), visibleFrame(visibleFrame), wallColor(sf::Color(96, 96, 96))
		{
			ShapeCubes wallsCubes;
			for (int i = 0; i < width; i++)
			{
				wallsCubes.addCube(Cube(i, height - 1, Cube::mtWall, wallColor));
			}

			wallsCubes.addCube(Cube(0, -1, Cube::mtVoid, wallColor));
			wallsCubes.addCube(Cube(width - 1, -1, Cube::mtVoid, wallColor));

			for (int j = -visibleFrame; j < height; j++)
			{
				wallsCubes.addCube(Cube(0, j, Cube::mtWall, wallColor));
				wallsCubes.addCube(Cube(width - 1, j, Cube::mtWall, wallColor));
			}
			walls.setCubes(wallsCubes);
		}

		void WallsController::processTimeStep(float dt)
		{
			walls.processTimeStep(dt);
			wallsKinematics.processTimeStep(dt);

			switch (state)
			{
			case sIdle:
				// Do nothing, just wait
				break;

			case sMovingDown:

				if (!wallsKinematics.isMovingVertically())
				{
					Logger::DEFAULT.logInfo("down ok");
					state = sIdle;
				}
				break;
			}
		}

		void WallsController::addTopBricks(int count)
		{
			ShapeCubes wallsCubes = walls.getCubes();
			for (int j = - visibleFrame; j >= -count - visibleFrame; j--)
			{
				wallsCubes.addCube(Cube(0, j, Cube::mtWall, wallColor));
				wallsCubes.addCube(Cube(width - 1, j, Cube::mtWall, wallColor));
			}
			walls.setCubes(wallsCubes);
		}

		bool WallsController::anyCollisions(const ShapeCubes& shape)
		{
			Shape shp;
			shp.setCubes(shape);
			ShapeDynamics sd(shp);

			sd.addObstacle(walls);

			return sd.anyCollisions();
		}

		void WallsController::startFalling(int count)
		{
			// Here we should emulate endless walls,
			// so adding the new bricks to the top
			addTopBricks(count);

			// removing the invisible bricks which we will never see again
			ShapeCubes wallsCubes = walls.getCubes();
			wallsCubes.removeAllBelow(height + visibleFrame);
			walls.setCubes(wallsCubes);

			state = sMovingDown;
			wallsKinematics.moveVertical(count, ParabolicPhaseProcessingFunction(), velocityController.getFallingDownFiredDuration());
			Logger::DEFAULT.logInfo("down");
		}

		WallsController::~WallsController()
		{
		}
	}
}
