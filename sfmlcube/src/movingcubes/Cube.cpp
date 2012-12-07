/*
 * Cube.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include "Cube.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		// Cube functions

		Cube::Cube(int x, int y, Cube::ModelType modelType, sf::Color color):
			 modelType(modelType),
			 color(color),
			 x(x), y(y)

		{
		}

		Cube::Cube():
			 modelType(Cube::mtPlaying),
			 color(color),
			 x(x), y(y)
		{
		}

		bool Cube::operator == (const Cube& other)
		{
			return this->x == other.x &&
			       this->y == other.y &&
			       this->modelType == other.modelType;
		}

		bool Cube::operator != (const Cube& other)
		{
			return !((*this) == other);
		}


	}

}
