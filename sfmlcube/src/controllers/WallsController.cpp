/*
 * WallsController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#include <SFML/Graphics/Color.hpp>

#include "../movingcubes/Cube.h"

#include "WallsController.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		WallsController::WallsController(int width, int height) :
				width(width), height(height)
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

		WallsController::~WallsController()
		{
		}
	}
}