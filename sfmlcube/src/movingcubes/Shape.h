/*
 * CubesGroup.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <list>

#include <SFML/System/NonCopyable.hpp>

#include "transitions/Transition.h"
#include "Cube.h"
#include "ShapeContainer.h"

using namespace std;
using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace movingcubes
	{
		enum RotatingCenterType
		{
			rctCenter, rctCorner
		};

		class Shape : public ShapeContainer
		{
		private:
			list<Cube> cubes;
		public:
			// Sliding
			float slidingX, slidingY;
			// Rotating animation
			RotatingCenterType rotatingCenterType;
			int rotatingCenterX, rotatingCenterY;
			float rotatingAngle;	// 1 = 90 degrees

			// Ambient color
			sf::Color ambient;
			float transparency;

			Shape() :
				slidingX(0),
				slidingY(0),

				rotatingCenterType(rctCenter),
				rotatingCenterX(0),
				rotatingCenterY(0),
				rotatingAngle(0),

				ambient(128, 128, 128, 255),
				transparency(1.0)
			{
			}

			const list<Cube>& getCubes() const { return cubes; }
			void addCube(const Cube& cube)
			{
				cubes.push_back(cube);
			}
			void removeCube(int x, int y)
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

			void halfDesaturateCubes()
			{
				for (list<Cube>::iterator iter = cubes.begin(); iter != cubes.end(); iter++)
				{
					sf::Color cl = (*iter).color;
					float avgColor = (cl.r + cl.g + cl.b) / 3;

					cl.r = (cl.r + avgColor) / 2;
					cl.g = (cl.g + avgColor) / 2;
					cl.b = (cl.b + avgColor) / 2;

					(*iter).color = cl;
				}
			}

			void clear() { cubes.clear(); }

			void moveVerticalNoTransition(int cells);
			void moveHorizontalNoTransition(int cells);
			void rotateNoTransition(int angle);

			virtual const Shape& getShape() const { return *this; }
			virtual void setShape(const Shape& shape) { *this = shape; }

			int getLeft() const;
			int getRight() const;
			int getTop() const;
			int getBottom() const;

			list<Cube> cubeAt(int i, int j) const;

			void setRotatingCenter(int centerX, int centerY, RotatingCenterType value)
			{
				rotatingCenterX = centerX;
				rotatingCenterY = centerY;
				rotatingCenterType = value;
			}

			int getRotatingCenterX() const { return rotatingCenterX; }
			int getRotatingCenterY() const { return rotatingCenterY; }
			RotatingCenterType getRotatingCenterType() const { return rotatingCenterType; }

			bool operator == (const Shape& other);
			bool operator != (const Shape& other);

			Shape& operator += (const Shape& other);

			virtual ~Shape() {}
		};
	}
}
#endif
