/*
 * CubesGroup.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include "CubesGroup.h"

#ifndef NULL
#define NULL	0
#endif

namespace sfmlcubes
{

	void CubesGroup::advanceStep(double delta)
	{
		horizontalTransition.advanceStep(delta);
		verticalTransition.advanceStep(delta);
		rotateTransition.advanceStep(delta);
	}

	void CubesGroup::glDraw(int dx, int dy)
	{
		for (list<Cube>::const_iterator citer = getCubes().begin();
			 citer != getCubes().end();
			 citer ++)
		{
			(*citer).glDraw(dx, dy);
		}
	}

	int CubesGroup::getLeft()
	{
		int left = (*getCubes().begin()).x;
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			if ((*iter).x < left) left = (*iter).x;
		}
		return left;
	}

	int CubesGroup::getRight()
	{
		int right = (*getCubes().begin()).x;
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			if ((*iter).x > right) right = (*iter).x;
		}
		return right;
	}

	int CubesGroup::getTop()
	{
		int top = (*getCubes().begin()).x;
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			if ((*iter).y < top) top = (*iter).y;
		}
		return top;
	}

	int CubesGroup::getBottom()
	{
		int bottom = (*getCubes().begin()).x;
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			if ((*iter).y > bottom) bottom = (*iter).y;
		}
		return bottom;
	}

	void CubesGroup::moveDown()
	{
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			(*iter).y ++;
		}
		verticalTransition.setSourceY(-1.0);
		verticalTransition.setPhase(0);
	}

	void CubesGroup::moveRight()
	{
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			(*iter).x ++;
		}
		horizontalTransition.setSourceX(-1.0);
		horizontalTransition.setPhase(0);
	}

	void CubesGroup::moveLeft()
	{
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			(*iter).x --;
		}
		horizontalTransition.setSourceX(1.0);
		horizontalTransition.setPhase(0);
	}

	Cube* CubesGroup::cubeAt(int i, int j)
	{
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			if ((*iter).x == i && (*iter).y == j)
			{
				return &(*iter);
			}
		}
		return NULL;
	}

	void CubesGroup::rotateCW(int angle)
	{
		// Searching for anything in our radius
		for (int i = getLeft(); i <= getRight(); i++)
		for (int j = getTop(); j <= getBottom(); j++)
		{
			// Calculating 3 images for our position
			int ik[4], jk[4];
			int i0 = rotatingCenterX, j0 = rotatingCenterY;

			if (crct == crctCenterOfCube)
			{
				// Making the 90 degrees rotating group
				ik[0] = i;
				jk[0] = j;
				for (int k = 1; k < 4; k++)
				{
					ik[k] = i0 - jk[k - 1] + j0;
					jk[k] = j0 + ik[k - 1] - i0;
				}
			}
			else if (crct == crctCornerOfCube)
			{
				// Making the 90 degrees rotating group
				ik[0] = i;
				jk[0] = j;
				for (int k = 1; k < 4; k++)
				{
					ik[k] = i0 - jk[k - 1] + j0 - 1;
					jk[k] = j0 + ik[k - 1] - i0;
				}
			}

			// Making the group array
			Cube* src = cubeAt(ik[0], jk[0]);

			if (src != NULL)
			{
				// Rotating the group
				int k = (4 - angle) % 4;
				src->x = ik[k];
				src->y = jk[k];
			}
		}

		rotateTransition.setRotatingCenter(rotatingCenterX, rotatingCenterY, crct);
		rotateTransition.setAngle(angle);
		rotateTransition.setPhase(0);
	}

}
