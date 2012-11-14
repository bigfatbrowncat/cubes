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
	CubesField::CubesField(int width, int height): width(width), height(height)
	{
		cubesData = new Cube[width * height];
	}

	CubesField::~CubesField()
	{
		delete [] cubesData;
	}

	Cube& CubesField::getCube(int i, int j)
	{
		return cubesData[width * j + i];
	}

	void CubesField::setCube(int i, int j, const Cube& value)
	{
		cubesData[width * j + i] = value;
	}

	bool CubesField::calculateFalling(CubesSlidingType cst)
	{
		vector<XY> falling_cube_coords;
		for (int i = 0; i < width; i++)
		for (int j = height - 1; j >= 0; j--)
		{
			if ((!cubesData[j * width + i].empty) && cubesData[j * width + i].freeMoving)
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
						 !(cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x].freeMoving))
				{
					// It's on another cube
					canFall = false;
					break;
				}
			}
		}

		// Do the sliding
		if (canFall)
		{
			if (cst == cstSlidingAnimation)
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					// Starting sliding animation
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].verticalSlidingDirection = cvsdDown;
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].verticalSlidingPhase = 0;
				}
			}
			else
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x] =
							cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x];

					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].empty = true;
					cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x].verticalSlidingPhase = 0;
					cubesData[(falling_cube_coords[k].y + 1) * width + falling_cube_coords[k].x].verticalSlidingDirection = cvsdNone;
				}
			}
		}
		else
		{
			// Stop falling
			for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				cubesData[j * width + i].freeMoving = false;
				cubesData[j * width + i].verticalSlidingDirection = cvsdNone;
			}
		}

		return canFall;
	}

	bool CubesField::tryMoveRight(CubesSlidingType cst)
	{
		vector<XY> falling_cube_coords;
		for (int i = width - 1; i >= 0; i--)
		for (int j = 0; j < height; j++)
		{
			if ((!cubesData[j * width + i].empty) && cubesData[j * width + i].freeMoving)
			{
				falling_cube_coords.push_back(XY(i, j));
			}
		}

		bool can_move = true;

		if (falling_cube_coords.size() == 0)
		{
			can_move = false;
		}
		else
		{
			for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
			{
				if (falling_cube_coords[k].x == width - 1)
				{
					// It's near the wall
					can_move = false;
					break;
				}
				else if (!(cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x + 1].empty) &&
						 !(cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x + 1].freeMoving))

				{
					// It's on another cube
					can_move = false;
					break;
				}
			}

		}

		// Do the sliding
		if (can_move)
		{
			if (cst == cstSlidingAnimation)
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					if (cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].horizontalSlidingDirection == chsdNone)
					{
						// Starting sliding animation
						cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].horizontalSlidingDirection = chsdRight;
						cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].horizontalSlidingPhase = 0;
					}
				}
			}
			else
			{
				for (unsigned int k = 0; k < falling_cube_coords.size(); k++)
				{
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x + 1] =
							cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x];

					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x].empty = true;
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x + 1].horizontalSlidingPhase = 0;
					cubesData[falling_cube_coords[k].y * width + falling_cube_coords[k].x + 1].horizontalSlidingDirection = chsdNone;
				}
			}
		}

		return can_move;
	}
}
