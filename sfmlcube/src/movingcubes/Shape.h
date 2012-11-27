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

using namespace std;
using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Shape
		{
		private:
			list<Cube> cubes;
		public:
			// Sliding
			float slidingX, slidingY;
			// Rotating animation
			Cube::RotatingCenterType rotatingCenterType;
			int rotatingCenterX, rotatingCenterY;
			float rotatingAngle;	// 1 = 90 degrees

			// Ambient color
			sf::Color ambientStatic;
			sf::Color ambientDynamic;
			float transparency;

			Shape() :
				slidingX(0),
				slidingY(0),

				rotatingCenterType(Cube::rctCenter),
				rotatingCenterX(0),
				rotatingCenterY(0),
				rotatingAngle(0),

				ambientStatic(128, 128, 128, 255),
				ambientDynamic(255, 255, 255, 255),
				transparency(1.0)
			{
			}

			const list<Cube>& getCubes() const { return cubes; }
			void addCube(const Cube& cube)
			{
				cubes.push_back(cube);
			}


			void clear() { cubes.clear(); }

			void moveVerticalNoTransition(int cells);
			void moveHorizontalNoTransition(int cells);
			void rotateNoTransition(int angle);

			int getLeft();
			int getRight();
			int getTop();
			int getBottom();

			list<Cube> cubeAt(int i, int j) const;

			void setRotatingCenter(int centerX, int centerY, Cube::RotatingCenterType value)
			{
				rotatingCenterX = centerX;
				rotatingCenterY = centerY;
				rotatingCenterType = value;
			}

			int getRotatingCenterX() const { return rotatingCenterX; }
			int getRotatingCenterY() const { return rotatingCenterY; }
			Cube::RotatingCenterType getRotatingCenterType() const { return rotatingCenterType; }

			void glDraw(int dx, int dy) const;

			bool operator == (const Shape& other);
			bool operator != (const Shape& other);

			Shape& operator += (const Shape& other);
		};
	}
}
#endif
