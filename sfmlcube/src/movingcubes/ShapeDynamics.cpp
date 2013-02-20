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

		ShapeDynamics::ShapeDynamics(const Shape& shape) :
				shape(shape)
		{
		}

		void ShapeDynamics::addObstacle(const Shape& obstacle)
		{
			obstacles.push_back(&obstacle);
		}
		void ShapeDynamics::removeObstacle(const Shape& obstacle)
		{
			obstacles.remove(&obstacle);
		}
		void ShapeDynamics::clearObstacles()
		{
			obstacles.clear();
		}

		bool ShapeDynamics::anyCollisions(const ShapeCubes& shape)
		{
			for (list<Cube>::const_iterator citer = shape.getCubes().begin(); citer != shape.getCubes().end(); citer++)
			{
				int i = (*citer).x;
				int j = (*citer).y;

				// Checking if there is a cube of an obstacle under our cube
				for (list<const Shape*>::const_iterator sciter = obstacles.begin(); sciter != obstacles.end(); sciter++)
				{
					if (!(*sciter)->getCubes().cubeAt(i, j).empty()) return true;
				}
			}

			return false;
		}

		bool ShapeDynamics::anyCollisions()
		{
			return anyCollisions(shape.getCubes());
		}

		bool ShapeDynamics::canMoveDown()
		{
			ShapeCubes tmp(shape.getCubes());
			tmp.moveVerticalNoTransition(1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canMoveLeft()
		{
			ShapeCubes tmp(shape.getCubes());
			tmp.moveHorizontalNoTransition(-1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canMoveRight()
		{
			ShapeCubes tmp(shape.getCubes());
			tmp.moveHorizontalNoTransition(1);
			bool res = !anyCollisions(tmp);

			return res;
		}

		bool ShapeDynamics::canRotate(int angle)
		{
			ShapeCubes tmp(shape.getCubes());
			tmp.rotateNoTransition(angle);
			bool res = !anyCollisions(tmp);

			return res;
		}


		ShapeDynamics::~ShapeDynamics()
		{
		}

	}
}
