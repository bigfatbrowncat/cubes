/*
 * Dynamic.h
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#ifndef SHAPEDYNAMICS_H_
#define SHAPEDYNAMICS_H_

#include <list>

#include "ShapeContainer.h"
#include "Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{

		class ShapeDynamics
		{
		private:
			ShapeContainer& shapeContainer;
			list<const ShapeContainer*> obstacles;
			bool anyCollisions(const Shape& shape);
		public:
			ShapeDynamics(ShapeContainer& shapeContainer);

			void addObstacle(const ShapeContainer& obstacle);
			void removeObstacle(const ShapeContainer& obstacle);
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
