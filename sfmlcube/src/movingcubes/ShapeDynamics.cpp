/*
 * Dynamic.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#include "ShapeDynamics.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		ShapeDynamics::ShapeDynamics(ShapeContainer& shapeContainer) :
				shapeContainer(shapeContainer)
		{
		}

		void ShapeDynamics::addObstacle(const ShapeContainer& obstacle)
		{
			obstacles.push_back(&obstacle);
		}
		void ShapeDynamics::removeObstacle(const ShapeContainer& obstacle)
		{
			obstacles.remove(&obstacle);
		}
		void ShapeDynamics::clearObstacles()
		{
			obstacles.clear();
		}

		bool ShapeDynamics::anyCollisions(const Shape& shape)
		{
			for (list<Cube>::const_iterator citer = shape.getCubes().begin(); citer != shape.getCubes().end(); citer++)
			{
				int i = (*citer).x;
				int j = (*citer).y;

				// Checking if there is a cube of an obstacle under our cube
				for (list<const ShapeContainer*>::const_iterator sciter = obstacles.begin(); sciter != obstacles.end(); sciter++)
				{
					if (!(*sciter)->getShape().cubeAt(i, j).empty()) return true;
				}
			}

			return false;
		}

		bool ShapeDynamics::anyCollisions()
		{
			Shape shape = shapeContainer.getShape();
			return anyCollisions(shape);
		}

		bool ShapeDynamics::canMoveDown()
		{
			Shape tmp = shapeContainer.getShape();
			tmp.moveVerticalNoTransition(1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canMoveLeft()
		{
			Shape tmp = shapeContainer.getShape();
			tmp.moveHorizontalNoTransition(-1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canMoveRight()
		{
			Shape tmp = shapeContainer.getShape();
			tmp.moveHorizontalNoTransition(1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canRotate(int angle)
		{
			Shape tmp = shapeContainer.getShape();
			tmp.rotateNoTransition(angle);
			bool res = !anyCollisions(tmp);

			return res;
		}


		ShapeDynamics::~ShapeDynamics()
		{
		}

	}
}
