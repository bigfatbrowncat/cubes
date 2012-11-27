/*
 * WallsController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef WALLSCONTROLLER_H_
#define WALLSCONTROLLER_H_

#include "movingcubes/Shape.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	class WallsController
	{
		Shape walls;
		int width, height;
	public:
		WallsController(int width, int height);

		const Shape& getWalls() const { return walls; }

		virtual ~WallsController();
	};
}
#endif
