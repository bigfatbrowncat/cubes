/*
 * Coordinates.cpp
 *
 *  Created on: Dec 13, 2012
 *      Author: imizus
 */

#include <math.h>

#include "Coordinates.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		Coordinates::Coordinates() :
				x(0), y(0), z(0)
		{

		}
		Coordinates::Coordinates(float x, float y, float z) :
				x(x), y(y), z(z)
		{

		}

		Coordinates Coordinates::rotate(float angle, float vx, float vy, float vz) const
		{
			float norm = sqrt(vx*vx + vy*vy + vz*vz);

			// Normalizing the rotation vector
			vx /= norm;
			vy /= norm;
			vz /= norm;

			// Calculating the matrix

/*          Here is the matrix of glRotate
 *
 * 		    |   x^2*(1-c)+c     x*y*(1-c)-z*s   x*z*(1-c)+y*s   0   |
		R = |   y*x*(1-c)+z*s   y^2*(1-c)+c     y*z*(1-c)-x*s   0   |
		    |   x*z*(1-c)-y*s   y*z*(1-c)+x*s   z^2*(1-c)+c     0   |
		    |   0               0               0               1   |*/

			float s = sin(angle);
			float c = cos(angle);

		    float Rxx = vx*vx * (1-c) + c;
		    float Ryx = vx*vy * (1-c) - vz*s;
		    float Rzx = vx*vz * (1-c) + vy*s;

		    float Rxy = vy*vx * (1-c) + vz*s;
		    float Ryy = vy*vy * (1-c) + c;
		    float Rzy = vy*vz * (1-c) - vx*s;

		    float Rxz = vx*vz * (1-c) - vy*s;
		    float Ryz = vy*vz * (1-c) + vx*s;
		    float Rzz = vz*vz * (1-c) + c;

		    // Applying the matrix
			float xr, yr, zr;
			xr = Rxx * x + Ryx * y + Rzx * z;
			yr = Rxy * x + Ryy * y + Rzy * z;
			zr = Rxz * x + Ryz * y + Rzz * z;

			return Coordinates(xr, yr, zr);
		}

		Coordinates Coordinates::scale(float px, float py, float pz) const
		{
			return Coordinates(x * px, y * py, z * pz);
		}
		Coordinates Coordinates::translate(float dx, float dy, float dz) const
		{
			return Coordinates(x + dx, y + dy, z + dz);
		}

		Coordinates Coordinates::project(float fovy, float aspect, float zNear, float zFar) const
		{
			// Calculating the matrix

/*          Here is the matrix of glRotate
 *
 * 		    |   fovy / aspect   0               0                                    0                                   |
 *      R = |   0               f               0                                    0                                   |
 *          |   0               0               (zFar + zNear) / (zNear - zFar)      2 * zFar * zNear / (zNear - zFar)   |
 *          |   0               0              -1                                    0                                   |
 */
			float f = 1.0 / tan(fovy / 2);

		    float Rxx = f / aspect;
		    float Ryy = f;
		    float Rzz = (zFar + zNear) / (zNear - zFar);
		    float Rwz = 2 * zFar * zNear / (zNear - zFar);
		    //float Rzw = -1;

		    // Applying the matrix
			float xr, yr, zr;
			xr = Rxx * x;
			yr = Ryy * y;
			zr = Rzz * z + Rwz;

			return Coordinates(xr, yr, zr);
		}


		Coordinates::~Coordinates()
		{

		}

	}
}
