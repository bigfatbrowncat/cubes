/*
 * CubesField.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <vector>

#include <SFML/Graphics.hpp>

#include "sfmlcubes.h"
#include "CubesField.h"
#include "Logger.h"

using namespace std;

namespace sfmlcubes
{
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
