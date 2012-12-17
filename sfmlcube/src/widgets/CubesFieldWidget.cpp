/*
 * CubesFieldWidget.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "CubesFieldWidget.h"

namespace sfmlcubes
{
	namespace widgets
	{
		CubesFieldWidget::CubesFieldWidget(const CubesField& cubesField, const sf::Font& font) :
				cubesField(cubesField),
				cubePainter(CubePainter::uField),
				shapePainter(cubePainter)

		{

		}

		Coordinates CubesFieldWidget::fromCubeInShapeCoordsToFieldCoords(sf::RenderTarget& target, const Shape& shape, const CubeCoordinates& currentCubeCoords, const Coordinates& coordsInTheCubeSpace) const
		{
			float k = (float)target.getSize().y / 480;
			Coordinates res = shapePainter.fromCubeInShapeCoordsToShapeCoords(shape, currentCubeCoords, coordsInTheCubeSpace);

			float delta_x = (cubesField.getWidth() - 0.5) / 2;
			float delta_y = (cubesField.getHeight() - 0.5) / 2;
			float cubeSize = 30;
			res = res.translate(-delta_x, delta_y, 0.f);

			res = res.scale(cubeSize, cubeSize, cubeSize);

			res = res.translate(0.f, 0.f, -300.f);

			float aspect = (float)target.getSize().x / target.getSize().y;
			res = res.project(100.0f, aspect, 1.f, 1000.f);

			// Here we have a magic constant
			float magic = 122.0 / 480;

			res = res.scale(- k * magic,
					          k * magic / aspect, 1);

			res = res.translate(target.getSize().x / 2, target.getSize().y / 2, 0);
			return res;
		}

		void CubesFieldWidget::drawBoard(sf::RenderTarget& target)
		{
	        // Setting perspective
	        glMatrixMode(GL_PROJECTION);
		    glLoadIdentity();
		    gluPerspective(100.f, (float)target.getSize().x / target.getSize().y, 1.f, 1000.f);

		    // Dawing models
		    glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.f, 0.f, -300.f);

			//glRotatef(0, 1.f, 0.f, 0.f);
			//glRotatef(0, 0.f, 1.f, 0.f);
			//glRotatef(0, 0.f, 0.f, 1.f);

			// Translating the board center to the center of the screen
			float delta_x = (cubesField.getWidth() - 0.5) / 2;
			float delta_y = (cubesField.getHeight() - 0.5) / 2;
			float cubeSize = 30;

			glScalef(cubeSize, cubeSize, cubeSize);
			glTranslatef(-delta_x, delta_y, 0.f);

			shapePainter.paint(cubesField.getWallsController().getShape());
			shapePainter.paint(cubesField.getFallingShapeController().getShape());

			list<Shape> shps = cubesField.getFallenController().getShapes();

			for (list<Shape>::const_iterator iter = shps.begin();
				 iter != shps.end();
				 iter++)
			{
				shapePainter.paint(*iter);
			}
		}

		CubesFieldWidget::~CubesFieldWidget()
		{
		}
	}
}
