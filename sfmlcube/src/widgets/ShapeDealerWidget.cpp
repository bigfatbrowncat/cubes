/*
 * ShapeDealerWidget.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>

#include "ShapeDealerWidget.h"

namespace sfmlcubes
{
	namespace widgets
	{

		ShapeDealerWidget::ShapeDealerWidget(const ShapeDealer& shapeDealer) :
				shapeDealer(shapeDealer),
				cubePainter(CubePainter::uPrediction),
				shapePainter(cubePainter)
		{
		}

		void ShapeDealerWidget::drawNextShape(sf::RenderTexture& win)
		{
	    	glMatrixMode(GL_PROJECTION);
	    	Shape dealingShape = shapeDealer.getShape();

	    	glLoadIdentity();
	    	gluPerspective(35.f, 1, 1, 1000);

			float cubeSize = 40;

	    	/*glViewport();*/

			glViewport(x, y, width, height);

	    	glMatrixMode(GL_MODELVIEW);
	    	glLoadIdentity();
		    glTranslatef(0.f, 0.f, -300.f);

			// Translating the board center to the center of the screen

			glTranslatef(cubeSize * 1.4,
			             cubeSize * 1.4,
			             0.f);
			glRotatef(30, 0.0, -1, -0.5);
			glScalef(cubeSize, cubeSize, cubeSize);

			dealingShape.moveHorizontalNoTransition(-dealingShape.getRight());
			dealingShape.moveVerticalNoTransition(-dealingShape.getTop());
			shapePainter.paint(dealingShape);
		}

		ShapeDealerWidget::~ShapeDealerWidget()
		{

		}

	}
}
