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

		ShapeDynamics::ShapeDynamics()
		{
		}

		void ShapeDynamics::setShape(Shape& shape)
		{
			this->shape = shape;
		}
		void ShapeDynamics::addObstacle(const Shape& obstacle)
		{
			obstacles.push_back(obstacle);
		}
		void ShapeDynamics::removeObstacle(const Shape& obstacle)
		{
			obstacles.remove(obstacle);
		}
		void ShapeDynamics::clearObstacles()
		{
			obstacles.clear();
		}

		bool ShapeDynamics::anyCollisions()
		{
			for (list<Cube>::const_iterator citer = shape.getCubes().begin(); citer != shape.getCubes().end(); citer++)
			{
				int i = (*citer).x;
				int j = (*citer).y;

				// Checking if there is a cube of an obstacle under our cube
				for (list<Shape>::const_iterator sciter = obstacles.begin(); sciter != obstacles.end(); sciter++)
				{
					if (!(*sciter).cubeAt(i, j).empty()) return true;
				}
			}

			return false;
		}

		bool ShapeDynamics::canMoveDown()
		{
			shape.moveVerticalNoTransition(1);
			bool res = !anyCollisions();
			shape.moveVerticalNoTransition(-1);

			return res;
		}

		bool ShapeDynamics::canMoveLeft()
		{
			shape.moveHorizontalNoTransition(-1);
			bool res = !anyCollisions();
			shape.moveHorizontalNoTransition(1);

			return res;
		}

		bool ShapeDynamics::canMoveRight()
		{
			shape.moveHorizontalNoTransition(1);
			bool res = !anyCollisions();
			shape.moveHorizontalNoTransition(-1);

			return res;
		}

		bool ShapeDynamics::canRotate(int angle)
		{
			shape.rotateNoTransition(angle);
			bool res = !anyCollisions();
			shape.rotateNoTransition(-angle);

			return res;
		}


		ShapeDynamics::~ShapeDynamics()
		{
			// TODO Auto-generated destructor stub
		}

	}
}
