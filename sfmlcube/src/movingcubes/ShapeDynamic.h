/*
 * Dynamic.h
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#ifndef SHAPEDYNAMIC_H_
#define SHAPEDYNAMIC_H_

#include <list>

#include "Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{

		class ShapeDynamic
		{
		private:
			Shape* shape;
			list<Shape*> obstacles;
		public:
			ShapeDynamic();

			void setShape(Shape& shape);
			void addObstacle(Shape& obstacle);
			void removeObstacle(Shape& obstacle);
			void clearObstacles();

			bool anyCollisions();
			bool canMoveDown();
			bool canMoveRight();
			bool canMoveLeft();
			bool canRotate(int angle);

			virtual ~ShapeDynamic();
		};

	}
}
#endif
