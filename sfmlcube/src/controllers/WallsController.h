/*
 * WallsController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef WALLSCONTROLLER_H_
#define WALLSCONTROLLER_H_

#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeContainer.h"


namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class WallsController : public ShapeContainer
		{
			Shape walls;
			int width, height;
		public:
			WallsController(int width, int height);

			const Shape& getShape() const { return walls; }
			void setShape(const Shape& shape) { walls = shape; }

			virtual ~WallsController();
		};
	}
}
#endif
