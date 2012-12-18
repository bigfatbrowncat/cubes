/*
 * CubesGroup.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>

#include "Shape.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		bool Shape::operator == (const Shape& other)
		{
			if (cubes.size() != other.getCubes().size())
			{
				return false;
			}

			for (list<Cube>::const_iterator citer = getCubes().begin();
				 citer != getCubes().end();
				 citer ++)
			{
				list<Cube> cx = other.cubeAt((*citer).x, (*citer).y);
				if (!cx.empty())
				{
					if (cx.back() != (*citer)) return false;
				}
			}

			return true;
		}

		bool Shape::operator != (const Shape& other)
		{
			return !((*this) == other);
		}

		Shape& Shape::operator += (const Shape& other)
		{
			for (list<Cube>::const_iterator iter = other.cubes.begin();
				 iter != other.cubes.end();
				 iter ++)
			{
				addCube(*iter);
			}
			return *this;
		}

		int Shape::getLeft() const
		{
			int left = (*getCubes().begin()).x;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).x < left) left = (*iter).x;
			}
			return left;
		}

		int Shape::getRight() const
		{
			int right = (*getCubes().begin()).x;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).x > right) right = (*iter).x;
			}
			return right;
		}

		int Shape::getTop() const
		{
			int top = (*getCubes().begin()).y;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).y < top) top = (*iter).y;
			}
			return top;
		}

		int Shape::getBottom() const
		{
			int bottom = (*getCubes().begin()).y;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).y > bottom) bottom = (*iter).y;
			}
			return bottom;
		}

		void Shape::moveVerticalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = cubes.begin();
				 iter != cubes.end();
				 iter ++)
			{
				(*iter).y += cells;
			}
			this->rotatingCenterY += cells;
		}

		void Shape::moveHorizontalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = cubes.begin();
				 iter != cubes.end();
				 iter ++)
			{
				(*iter).x += cells;
			}
			this->rotatingCenterX += cells;
		}

		void Shape::rotateNoTransition(int angle)
		{
			// Searching for anything in our radius
			for (list<Cube>::iterator iter = cubes.begin();
				 iter != cubes.end();
				 iter ++)
			{
				// Calculating 3 images for our position
				int ik[4], jk[4];
				int i0 = rotatingCenterX, j0 = rotatingCenterY;

				ik[0] = (*iter).x;
				jk[0] = (*iter).y;

				if (rotatingCenterType == rctCenter)
				{
					// Making the 90 degrees rotating group
					for (int k = 1; k < 4; k++)
					{
						ik[k] = i0 - jk[k - 1] + j0;
						jk[k] = j0 + ik[k - 1] - i0;
					}
				}
				else if (rotatingCenterType == rctCorner)
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

		}

		list<Cube> Shape::cubeAt(int i, int j) const
		{
			list<Cube> res;
			for (list<Cube>::const_iterator iter = getCubes().begin(); iter != getCubes().end(); iter ++)
			{
				if ((*iter).x == i && (*iter).y == j)
				{
					res.push_back(*iter);
				}
			}
			return res;
		}
	}
}
