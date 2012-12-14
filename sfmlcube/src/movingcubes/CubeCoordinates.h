/*
 * Coordinates.h
 *
 *  Created on: Dec 13, 2012
 *      Author: imizus
 */

#ifndef CUBECOORDINATES_H_
#define CUBECOORDINATES_H_

namespace sfmlcubes
{
	namespace movingcubes
	{

		class CubeCoordinates
		{
		private:
			int x, y;
		public:
			CubeCoordinates(int x, int y);

			int getX() const { return x; }
			int getY() const { return y; }

			virtual ~CubeCoordinates();
		};

	}
}
#endif
