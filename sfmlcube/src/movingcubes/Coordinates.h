/*
 * Coordinates.h
 *
 *  Created on: Dec 13, 2012
 *      Author: imizus
 */

#ifndef COORDINATES_H_
#define COORDINATES_H_

namespace sfmlcubes
{
	namespace movingcubes
	{

		class Coordinates
		{
		private:
			float x, y, z;
		public:
			Coordinates(float x, float y, float z);

			Coordinates rotate(float angle, float vx, float vy, float vz) const;
			Coordinates scale(float px, float py, float pz) const;
			Coordinates translate(float dx, float dy, float dz) const;
			Coordinates project(float fovy, float aspect, float zNear, float zFar) const;

			float getX() const { return x; }
			float getY() const { return y; }
			float getZ() const { return z; }

			virtual ~Coordinates();
		};

	}
}
#endif
