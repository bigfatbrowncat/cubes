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

		Coordinates ShapePainter::fromCubeInShapeCoordsToShapeCoords(const Shape& shape, CubeCoordinates currentCubeCoords, Coordinates coordsInTheCubeSpace) const
		{
			Coordinates res = coordsInTheCubeSpace;

			float xx = currentCubeCoords.getX();
			float yy = currentCubeCoords.getY();

			// Moving the cube to it's rotating center
			if (shape.getCubes().getRotatingCenterType() == rctCorner)
			{
				res = res.translate(1.0 / 2, -1.0 / 2, 0.f);
			}
			res = res.translate(-(shape.getCubes().getRotatingCenterX() - xx), shape.getCubes().getRotatingCenterY() - yy, 0.f);

			// Applying rotation
			double angle = 90 * shape.rotatingAngle->getValue();
			res = res.rotate(angle, 0.f, 0.f, -1.f);

			// Moving it back from rotating center
			res = res.translate(shape.getCubes().getRotatingCenterX() - xx, -(shape.getCubes().getRotatingCenterY() - yy), 0.f);
			if (shape.getCubes().getRotatingCenterType() == rctCorner)
			{
				res = res.translate(-1.0 / 2, 1.0 / 2, 0.f);
			}

			// ** Sliding **

			double hdistance = shape.slidingX->getValue();
			double vdistance = shape.slidingY->getValue();
			res = res.translate(hdistance, -vdistance, 0.f);

			res = res.translate(xx, -yy, 0.f);		// Translating the cube to it's cube coords

			return res;
		}

		void ShapePainter::paint(const Shape& shape) const
		{
			for (list<Cube>::const_iterator citer = shape.getCubes().getCubes().begin();
				 citer != shape.getCubes().getCubes().end();
				 citer ++)
			{
				glPushMatrix();
				{
					int xx = (*citer).x/* + dx*/;
					int yy = (*citer).y/* + dy*/;

					// ** Sliding **

					glTranslatef(xx, -yy, 0.f);		// Translating the cube to it's cube coords

					double hdistance = shape.slidingX->getValue();
					double vdistance = shape.slidingY->getValue();
					glTranslatef(hdistance, -vdistance, 0.f);

					// ** Rotating **

					// Moving it back from rotating center
					if (shape.getCubes().getRotatingCenterType() == rctCorner)
					{
						glTranslatef(-1.0 / 2, 1.0 / 2, 0.f);
					}
					glTranslatef(shape.getCubes().getRotatingCenterX() - xx, -(shape.getCubes().getRotatingCenterY() - yy), 0.f);

					// Applying rotation
					double angle = 90 * shape.rotatingAngle->getValue();
					glRotatef(angle, 0.f, 0.f, -1.f);

					// Moving the cube to it's rotating center
					glTranslatef(-(shape.getCubes().getRotatingCenterX() - xx), shape.getCubes().getRotatingCenterY() - yy, 0.f);
					if (shape.getCubes().getRotatingCenterType() == rctCorner)
					{
						glTranslatef(1.0 / 2, -1.0 / 2, 0.f);
					}

					sf::Color ambient = shape.ambient;
					cubePainter.setAmbient(ambient);
					cubePainter.setTransparency(shape.transparency->getValue());

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
