/*
 * CubesField.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <list>

#include <SFML/Graphics.hpp>

#include "sfmlcubes.h"
#include "CubesField.h"
#include "Logger.h"

using namespace std;

namespace sfmlcubes
{
	list<Cube*> CubesField::cubeAt(int i, int j)
	{
		list<Cube*> sum;
		for (list<CubesGroup*>::const_iterator iter = getCubesGroups().begin();
		     iter != getCubesGroups().end();
		     iter ++)
		{
			list<Cube*> cc = (*iter)->cubeAt(i, j);
			sum.merge(cc);
		}
		return sum;
	}

	void CubesField::glDraw(int dx, int dy)
	{
		for (list<CubesGroup*>::const_iterator iter = getCubesGroups().begin();
		     iter != getCubesGroups().end();
		     iter ++)
		{
			(*iter)->glDraw(dx, dy);
		}
	}

}
