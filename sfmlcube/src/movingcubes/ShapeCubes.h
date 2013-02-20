/*
 * ShapeCubes.h
 *
 *  Created on: Feb 19, 2013
 *      Author: imizus
 */

#ifndef SHAPECUBES_H_
#define SHAPECUBES_H_

#include <list>

#include "Cube.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		enum RotatingCenterType
		{
			rctCenter, rctCorner
		};

		class ShapeCubes
		{
		private:
			list<Cube> cubeList;
			int rotatingCenterX, rotatingCenterY;
			RotatingCenterType rotatingCenterType;

		public:
			ShapeCubes();
			virtual ~ShapeCubes();

			const list<Cube>& getCubeList() const { return cubeList; }
			void addCube(const Cube& cube);
			void removeAllBelow(int y);
			void removeCube(int x, int y);

			void changeToFallenColor();
			void clear() { cubeList.clear(); }

			void moveVerticalNoTransition(int cells);
			void moveHorizontalNoTransition(int cells);
			void rotateNoTransition(int angle);

			int getLeft() const;
			int getRight() const;
			int getTop() const;
			int getBottom() const;

			list<Cube> cubeAt(int i, int j) const;

			bool operator == (const ShapeCubes& other);
			bool operator != (const ShapeCubes& other);

			ShapeCubes& operator += (const ShapeCubes& other);

			bool isEmpty() { return cubeList.size() == 0; }

			void setRotatingCenter(int centerX, int centerY, RotatingCenterType value)
			{
				rotatingCenterX = centerX;
				rotatingCenterY = centerY;
				rotatingCenterType = value;
			}
			int getRotatingCenterX() const { return rotatingCenterX; }
			int getRotatingCenterY() const { return rotatingCenterY; }
			RotatingCenterType getRotatingCenterType() const { return rotatingCenterType; }


		};
	}
}
#endif
