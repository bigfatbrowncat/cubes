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

		Coordinates ShapePainter::fromCubeInShapeCoordsToShapeCoords(const ShapeState& shapeState, CubeCoordinates currentCubeCoords, Coordinates coordsInTheCubeSpace) const
		{
			Coordinates res = coordsInTheCubeSpace;
			const ShapeCubes& cubes = shapeState.getCubes();

			float xx = currentCubeCoords.getX();
			float yy = currentCubeCoords.getY();

			// Moving the cube to it's rotating center
			if (cubes.getRotatingCenterType() == rctCorner)
			{
				res = res.translate(1.0 / 2, -1.0 / 2, 0.f);
			}
			res = res.translate(-(cubes.getRotatingCenterX() - xx), cubes.getRotatingCenterY() - yy, 0.f);

			// Applying rotation
			double angle = 90 * shapeState.getRotatingAngle();
			res = res.rotate(angle, 0.f, 0.f, -1.f);

			// Moving it back from rotating center
			res = res.translate(cubes.getRotatingCenterX() - xx, -(cubes.getRotatingCenterY() - yy), 0.f);
			if (cubes.getRotatingCenterType() == rctCorner)
			{
				res = res.translate(-1.0 / 2, 1.0 / 2, 0.f);
			}

			// ** Sliding **

			double hdistance = shapeState.getSlidingX();
			double vdistance = shapeState.getSlidingY();
			res = res.translate(hdistance, -vdistance, 0.f);

			res = res.translate(xx, -yy, 0.f);		// Translating the cube to it's cube coords

			return res;
		}

		void ShapePainter::paint(const ShapeState& shapeState) const
		{
			const ShapeCubes& cubes = shapeState.getCubes();
			for (list<Cube>::const_iterator citer = cubes.getCubeList().begin();
				 citer != cubes.getCubeList().end();
				 citer ++)
			{
				glPushMatrix();
				{
					int xx = (*citer).x/* + dx*/;
					int yy = (*citer).y/* + dy*/;

					// ** Sliding **

					glTranslatef(xx, -yy, 0.f);		// Translating the cube to it's cube coords

					double hdistance = shapeState.getSlidingX();
					double vdistance = shapeState.getSlidingY();
					glTranslatef(hdistance, -vdistance, 0.f);

					// ** Rotating **

					// Moving it back from rotating center
					if (cubes.getRotatingCenterType() == rctCorner)
					{
						glTranslatef(-1.0 / 2, 1.0 / 2, 0.f);
					}
					glTranslatef(cubes.getRotatingCenterX() - xx, -(cubes.getRotatingCenterY() - yy), 0.f);

					// Applying rotation
					double angle = 90 * shapeState.getRotatingAngle();
					glRotatef(angle, 0.f, 0.f, -1.f);

					// Moving the cube to it's rotating center
					glTranslatef(-(cubes.getRotatingCenterX() - xx), cubes.getRotatingCenterY() - yy, 0.f);
					if (cubes.getRotatingCenterType() == rctCorner)
					{
						glTranslatef(1.0 / 2, -1.0 / 2, 0.f);
					}

					sf::Color ambient = shapeState.getAmbient();
					cubePainter.setAmbient(ambient);
					cubePainter.setTransparency(shapeState.getTransparency());

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
