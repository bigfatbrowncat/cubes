/*
 * CubesField.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <vector>

#include "CubesField.h"

using namespace std;

namespace sfmlcubes
{
	struct XY
	{
		int x, y;
		XY(int x, int y): x(x), y(y) {}
	};

	CubesField::CubesField(int width, int height): width(width), height(height)
	{
		cubesData = new Cube[width * height];
	}

	CubesField::~CubesField()
	{
		delete [] cubesData;
	}

	const Cube& CubesField::getCube(int i, int j)
	{
		return cubesData[width * j + i];
	}

	void CubesField::setCube(int i, int j, const Cube& value)
	{
		cubesData[width * j + i] = value;
	}

	void CubesField::resetAnimations()
	{
		for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			cubesData[j * width + i].slidingDirection = csdNone;
			cubesData[j * width + i].rotatingDirection = crdNone;
		}
	}

	bool CubesField::calculateSliding(CubesSlidingType cst)
	{
		// Enumerating falling cubes
		vector<XY> falling_cube_coords;
		for (int i = 0; i < width; i++)
		for (int j = height - 1; j >= 0; j--)
		{
			if (!cubesData[j * width + i].empty && cubesData[j * width + i].falling)
			{
				falling_cube_coords.push_back(XY(i, j));
			}
		}

		// Checking if they can fall
		bool canFall = true;

		if (falling_cube_coords.size() == 0)
		{
			canFall = false;
		}
		else
		{
			for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
			{
				if (falling_cube_coords[k].y == height - 1)
				{
					// It's on the floor
					canFall = false;
					break;
				}
				else if (!(cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x].empty) &&
						 !(cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x].falling))
				{
					// It's on another cube
					canFall = false;
					break;
				}
			}
		}

		// Do the sliding
		resetAnimations();
		if (canFall)
		{
			if (cst == cstSlidingAnimation)
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].slidingDirection = csdDown;
				}
			}
			else
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x] =
							cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x];

					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].empty = true;
				}
			}
		}
		else
		{
			// Stop falling
			for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				cubesData[j * width + i].falling = false;
			}
		}

		return canFall;
	}
}
