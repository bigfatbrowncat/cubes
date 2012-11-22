/*
 * CubesGroup.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include "CubesGroup.h"

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
		this->rotatingCenterY ++;
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
		this->rotatingCenterX ++;
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
		this->rotatingCenterX --;
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
		for (list<Cube>::iterator iter = getCubes().begin();
			 iter != getCubes().end();
			 iter ++)
		{
			// Calculating 3 images for our position
			int ik[4], jk[4];
			int i0 = rotatingCenterX, j0 = rotatingCenterY;

			ik[0] = (*iter).x;
			jk[0] = (*iter).y;

			if (rotatingCenterType == crctCenterOfCube)
			{
				// Making the 90 degrees rotating group
				for (int k = 1; k < 4; k++)
				{
					ik[k] = i0 - jk[k - 1] + j0;
					jk[k] = j0 + ik[k - 1] - i0;
				}
			}
			else if (rotatingCenterType == crctCornerOfCube)
			{
				// Making the 90 degrees rotating group
				for (int k = 1; k < 4; k++)
				{
					ik[k] = i0 - jk[k - 1] + j0 - 1;
					jk[k] = j0 + ik[k - 1] - i0;
				}
			}

			// Making the group array
			//Cube* src = cubeAt(ik[0], jk[0]);

			//if (src != NULL)
			{
				// Rotating the group
				int k = (4 + angle) % 4;
				(*iter).x = ik[k];
				(*iter).y = jk[k];
			}
		}

		rotateTransition.setSourceAngle(-angle);
		rotateTransition.setPhase(0);
	}

}
