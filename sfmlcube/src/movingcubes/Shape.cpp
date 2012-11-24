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
		void Shape::advanceStep(double delta)
		{
			mRotateTransition.advanceStep(delta);
			mHorizontalTransition.advanceStep(delta);
			mVerticalTransition.advanceStep(delta);
		}

		bool Shape::transitionIsInProgress() const
		{
			return mRotateTransition.isInProgress() ||
				   mHorizontalTransition.isInProgress() ||
				   mVerticalTransition.isInProgress();
		}

		void Shape::glDraw(int dx, int dy)
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
					if (rotatingCenterType == crctCornerOfCube)
					{
						glTranslatef(-1.0 / 2, 1.0 / 2, 0.f);
					}
					glTranslatef(rotatingCenterX - xx, -(rotatingCenterY - yy), 0.f);

					// Applying rotation
					double angle = 90 * rotatingAngle;
					glRotatef(angle, 0.f, 0.f, -1.f);

					// Moving the cube to it's rotating center
					glTranslatef(-(rotatingCenterX - xx), rotatingCenterY - yy, 0.f);
					if (rotatingCenterType == crctCornerOfCube)
					{
						glTranslatef(1.0 / 2, -1.0 / 2, 0.f);
					}

					(*citer).glDraw();
				}
				glPopMatrix();
			}

		}

		int Shape::getLeft()
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

		int Shape::getRight()
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

		int Shape::getTop()
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

		int Shape::getBottom()
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

		void Shape::moveVerticalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				(*iter).y += cells;
			}
			this->rotatingCenterY += cells;
		}

		void Shape::moveVertical(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			moveVerticalNoTransition(cells);
			mVerticalTransition = SlideYTransition(*this, longitude, function, -cells);
		}

		void Shape::moveHorizontalNoTransition(int cells)
		{
			for (list<Cube>::iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				(*iter).x += cells;
			}
			this->rotatingCenterX += cells;
		}

		void Shape::moveHorizontal(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			moveHorizontalNoTransition(cells);
			mHorizontalTransition = SlideXTransition(*this, longitude, function, -cells);
		}

		void Shape::rotateNoTransition(int angle)
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

		}

		void Shape::rotate(int angle, Transition::PhaseProcessingFunction function, float longitude)
		{
			rotateNoTransition(angle);
			mRotateTransition = RotateTransition(*this, longitude, function, -angle);
		}

		list<Cube*> Shape::cubeAt(int i, int j)
		{
			list<Cube*> res;
			for (list<Cube>::iterator iter = getCubes().begin();
				 iter != getCubes().end();
				 iter ++)
			{
				if ((*iter).x == i && (*iter).y == j)
				{
					res.push_back(&(*iter));
				}
			}
			return res;
		}
	}
}
