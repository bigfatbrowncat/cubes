/*
 * Dynamic.h
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#ifndef SHAPEDYNAMICS_H_
#define SHAPEDYNAMICS_H_

#include <list>

#include "Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{

		class ShapeDynamics
		{
		private:
			Shape shape;
			list<Shape> obstacles;
		public:
			ShapeDynamics();

			void setShape(Shape& shape);
			void addObstacle(const Shape& obstacle);
			void removeObstacle(const Shape& obstacle);
			void clearObstacles();

			bool anyCollisions();
			bool canMoveDown();
			bool canMoveRight();
			bool canMoveLeft();
			bool canRotate(int angle);

			virtual ~ShapeDynamics();
		};

	}
}
#endif
