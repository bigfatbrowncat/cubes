/*
 * ShapePainter.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>

#include "ShapePainter.h"

namespace sfmlcubes
{
	namespace widgets
	{

		ShapePainter::ShapePainter(CubePainter& cubePainter) :
				cubePainter(cubePainter)
		{

		}

		void ShapePainter::paint(const Shape& shape) const
		{
			for (list<Cube>::const_iterator citer = shape.getCubes().begin();
				 citer != shape.getCubes().end();
				 citer ++)
			{
				glPushMatrix();
				{
					int xx = (*citer).x/* + dx*/;
					int yy = (*citer).y/* + dy*/;

					glTranslatef(xx, -yy, 0.f);			// Translating the cube

					// ** Sliding **

					double hdistance = shape.slidingX;
					double vdistance = shape.slidingY;
					glTranslatef(hdistance, -vdistance, 0.f);

					// ** Rotating **

					// Moving it back from rotating center
					if (shape.rotatingCenterType == rctCorner)
					{
						glTranslatef(-1.0 / 2, 1.0 / 2, 0.f);
					}
					glTranslatef(shape.rotatingCenterX - xx, -(shape.rotatingCenterY - yy), 0.f);

					// Applying rotation
					double angle = 90 * shape.rotatingAngle;
					glRotatef(angle, 0.f, 0.f, -1.f);

					// Moving the cube to it's rotating center
					glTranslatef(-(shape.rotatingCenterX - xx), shape.rotatingCenterY - yy, 0.f);
					if (shape.rotatingCenterType == rctCorner)
					{
						glTranslatef(1.0 / 2, -1.0 / 2, 0.f);
					}

					sf::Color ambient = shape.ambientStatic * shape.ambientDynamic;
					cubePainter.setAmbient(ambient);
					cubePainter.setTransparency(shape.transparency);

					cubePainter.paint(*citer);
				}
				glPopMatrix();
			}
		}

		ShapePainter::~ShapePainter()
		{

		}

	}
}