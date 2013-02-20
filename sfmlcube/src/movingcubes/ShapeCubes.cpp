/*
 * ShapeCubes.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: imizus
 */

#include "ShapeCubes.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		ShapeCubes::ShapeCubes() :
			rotatingCenterX(0),
			rotatingCenterY(0),
			rotatingCenterType(rctCenter)
		{

		}

		void ShapeCubes::addCube(const Cube& cube)
		{
			cubes.push_back(cube);
		}

		void ShapeCubes::removeAllBelow(int y)
		{
			for (list<Cube>::iterator iter = cubes.begin(); iter != cubes.end();)
			{
				if ((*iter).y > y)
				{
					iter = cubes.erase(iter);
				}
				else
				{
					iter ++;
				}
			}
		}

		void ShapeCubes::removeCube(int x, int y)
		{
			for (list<Cube>::iterator iter = cubes.begin(); iter != cubes.end(); iter++)
			{
				if ((*iter).x == x && (*iter).y == y)
				{
					cubes.remove(*iter);
					return;
				}
			}
		}

		void ShapeCubes::changeToFallenColor()
		{
			for (list<Cube>::iterator iter = cubes.begin(); iter != cubes.end(); iter++)
			{
				sf::Color cl = (*iter).color;
				float avgColor = (cl.r + cl.g + cl.b) / 3;

				cl.r = (cl.r + 2 * avgColor) / 3 * 0.8;
				cl.g = (cl.g + 2 * avgColor) / 3 * 0.8;
				cl.b = (cl.b + 2 * avgColor) / 3 * 0.8;

				(*iter).color = cl;
			}
		}

		bool ShapeCubes::operator == (const ShapeCubes& other)
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

		bool ShapeCubes::operator != (const ShapeCubes& other)
		{
			return !((*this) == other);
		}

		ShapeCubes& ShapeCubes::operator += (const ShapeCubes& other)
		{
			for (list<Cube>::const_iterator iter = other.cubes.begin();
				 iter != other.cubes.end();
				 iter ++)
			{
				addCube(*iter);
			}
			return *this;
		}

		int ShapeCubes::getLeft() const
		{
			if (getCubes().size() == 0) return 0;
			int left = (*getCubes().begin()).x;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).x < left) left = (*iter).x;
			}
			return left;
		}

		int ShapeCubes::getRight() const
		{
			if (getCubes().size() == 0) return 0;
			int right = (*getCubes().begin()).x;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).x > right) right = (*iter).x;
			}
			return right;
		}

		int ShapeCubes::getTop() const
		{
			if (getCubes().size() == 0) return 0;
			int top = (*getCubes().begin()).y;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).y < top) top = (*iter).y;
			}
			return top;
		}

		int ShapeCubes::getBottom() const
		{
			if (getCubes().size() == 0) return 0;
			int bottom = (*getCubes().begin()).y;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).y > bottom) bottom = (*iter).y;
			}
			return bottom;
		}

		void ShapeCubes::moveVerticalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = cubes.begin();
				 iter != cubes.end();
				 iter ++)
			{
				(*iter).y += cells;
			}
			this->rotatingCenterY += cells;
		}

		void ShapeCubes::moveHorizontalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = cubes.begin();
				 iter != cubes.end();
				 iter ++)
			{
				(*iter).x += cells;
			}
			this->rotatingCenterX += cells;
		}

		void ShapeCubes::rotateNoTransition(int angle)
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

		list<Cube> ShapeCubes::cubeAt(int i, int j) const
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

		ShapeCubes::~ShapeCubes()
		{

		}
	}
}
