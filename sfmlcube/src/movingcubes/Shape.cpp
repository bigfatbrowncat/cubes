/*
 * CubesGroup.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <GL/gl.h>

#include "Shape.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		void Shape::glDraw(int dx, int dy) const
		{
			for (list<Cube>::const_iterator citer = getCubes().begin();
				 citer != getCubes().end();
				 citer ++)
			{
				glPushMatrix();
				{
					int xx = (*citer).x + dx;
					int yy = (*citer).y + dy;

					glTranslatef(xx, -yy, 0.f);			// Translating the cube

					// ** Sliding **

					double hdistance = slidingX;
					double vdistance = slidingY;
					glTranslatef(hdistance, -vdistance, 0.f);

					// ** Rotating **

					// Moving it back from rotating center
					if (rotatingCenterType == Cube::rctCorner)
					{
						glTranslatef(-1.0 / 2, 1.0 / 2, 0.f);
					}
					glTranslatef(rotatingCenterX - xx, -(rotatingCenterY - yy), 0.f);

					// Applying rotation
					double angle = 90 * rotatingAngle;
					glRotatef(angle, 0.f, 0.f, -1.f);

					// Moving the cube to it's rotating center
					glTranslatef(-(rotatingCenterX - xx), rotatingCenterY - yy, 0.f);
					if (rotatingCenterType == Cube::rctCorner)
					{
						glTranslatef(1.0 / 2, -1.0 / 2, 0.f);
					}

					sf::Color ambient = ambientStatic * ambientDynamic;
					Cube::cubeShader.setParameter("ambient", (float)ambient.r / 255, (float)ambient.g / 255, (float)ambient.b / 255, (float)ambient.a / 255);
					Cube::cubeShader.setParameter("transparency", transparency);
					(*citer).glDraw();
				}
				glPopMatrix();
			}

		}

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

		int Shape::getLeft()
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

		int Shape::getRight()
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

		int Shape::getTop()
		{
			int top = (*getCubes().begin()).x;
			for (list<Cube>::const_iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).y < top) top = (*iter).y;
			}
			return top;
		}

		int Shape::getBottom()
		{
			int bottom = (*getCubes().begin()).x;
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

				if (rotatingCenterType == Cube::rctCenter)
				{
					// Making the 90 degrees rotating group
					for (int k = 1; k < 4; k++)
					{
						ik[k] = i0 - jk[k - 1] + j0;
						jk[k] = j0 + ik[k - 1] - i0;
					}
				}
				else if (rotatingCenterType == Cube::rctCorner)
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
