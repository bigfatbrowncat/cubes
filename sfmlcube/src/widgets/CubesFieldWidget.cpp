/*
 * CubesFieldWidget.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>

#include "CubesFieldWidget.h"

namespace sfmlcubes
{
	namespace widgets
	{
		CubesFieldWidget::CubesFieldWidget(const CubesField& cubesField) :
				cubesField(cubesField)
		{

		}

		void CubesFieldWidget::drawBoard()
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

			cubesField.glDraw();
		}

		CubesFieldWidget::~CubesFieldWidget()
		{
		}
	}
}