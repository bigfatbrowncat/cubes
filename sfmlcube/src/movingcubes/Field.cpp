/*
 * CubesField.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <list>

#include <SFML/Graphics.hpp>

#include "Field.h"
#include "../Logger.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		void Field::advanceStep(double delta)
		{
			for (list<Shape*>::const_iterator iter = getCubesGroups().begin();
				 iter != getCubesGroups().end();
				 iter ++)
			{
				(*iter)->advanceStep(delta);
			}
		}

		bool Field::anyTransitionsInProgress()
		{
			for (list<Shape*>::const_iterator iter = getCubesGroups().begin();
				 iter != getCubesGroups().end();
				 iter ++)
			{
				if ((*iter)->transitionIsInProgress()) return true;
			}
			return false;
		}

		list<Cube*> Field::cubeAt(int i, int j)
		{
			list<Cube*> sum;
			for (list<Shape*>::const_iterator iter = getCubesGroups().begin();
				 iter != getCubesGroups().end();
				 iter ++)
			{
				list<Cube*> cc = (*iter)->cubeAt(i, j);
				sum.merge(cc);
			}
			return sum;
		}

		void Field::glDraw(int dx, int dy)
		{
			for (list<Shape*>::const_iterator iter = getCubesGroups().begin();
				 iter != getCubesGroups().end();
				 iter ++)
			{
				(*iter)->glDraw(dx, dy);
			}
		}
	}
}