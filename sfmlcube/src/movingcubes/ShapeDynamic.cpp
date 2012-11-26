/*
 * Dynamic.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#include "ShapeDynamic.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		ShapeDynamic::ShapeDynamic()
		{
		}

		void ShapeDynamic::setShape(Shape& shape)
		{
			this->shape = &shape;
		}
		void ShapeDynamic::addObstacle(Shape& obstacle)
		{
			obstacles.push_back(&obstacle);
		}
		void ShapeDynamic::removeObstacle(Shape& obstacle)
		{
			obstacles.remove(&obstacle);
		}
		void ShapeDynamic::clearObstacles()
		{
			obstacles.clear();
		}

		bool ShapeDynamic::anyCollisions()
		{
			for (list<Cube>::const_iterator citer = shape->getCubes().begin(); citer != shape->getCubes().end(); citer++)
			{
				int i = (*citer).x;
				int j = (*citer).y;

				// Checking if there is a cube of an obstacle under our cube
				for (list<Shape*>::const_iterator sciter = obstacles.begin(); sciter != obstacles.end(); sciter++)
				{
					if (!(*sciter)->cubeAt(i, j).empty()) return true;
				}
			}

			return false;
		}

		bool ShapeDynamic::canMoveDown()
		{
			shape->moveVerticalNoTransition(1);
			bool res = !anyCollisions();
			shape->moveVerticalNoTransition(-1);

			return res;
		}

		bool ShapeDynamic::canMoveLeft()
		{
			shape->moveHorizontalNoTransition(-1);
			bool res = !anyCollisions();
			shape->moveHorizontalNoTransition(1);

			return res;
		}

		bool ShapeDynamic::canMoveRight()
		{
			shape->moveHorizontalNoTransition(1);
			bool res = !anyCollisions();
			shape->moveHorizontalNoTransition(-1);

			return res;
		}

		bool ShapeDynamic::canRotate(int angle)
		{
			shape->rotateNoTransition(angle);
			bool res = !anyCollisions();
			shape->rotateNoTransition(-angle);

			return res;
		}


		ShapeDynamic::~ShapeDynamic()
		{
			// TODO Auto-generated destructor stub
		}

	}
}
