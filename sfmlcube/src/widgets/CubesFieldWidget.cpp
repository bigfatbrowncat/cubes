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
				animatedPopupsPainter(cubesField.getScoreCounter().getAnimatedPopupsManager(), font),
				cubePainter(CubePainter::uField),
				shapePainter(cubePainter)

		{

		}

		void CubesFieldWidget::drawBoard(sf::RenderTarget& target)
		{
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


			target.draw(animatedPopupsPainter, sf::RenderStates::Default);

		}

		CubesFieldWidget::~CubesFieldWidget()
		{
		}
	}
}
