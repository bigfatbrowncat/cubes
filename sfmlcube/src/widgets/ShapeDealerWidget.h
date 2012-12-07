/*
 * ShapeDealerWidget.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef SHAPEDEALERWIDGET_H_
#define SHAPEDEALERWIDGET_H_

#include "../controllers/ShapeDealer.h"

#include "CubePainter.h"
#include "ShapePainter.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class ShapeDealerWidget
		{
		private:
			const ShapeDealer& shapeDealer;
			int x, y, width, height;
			CubePainter cubePainter;
			ShapePainter shapePainter;
		public:
			ShapeDealerWidget(const ShapeDealer& shapeDealer);
			void setViewport(int x, int y, int width, int height)
			{
				this->x = x; this->y = y; this->width = width; this->height = height;
			}
			void drawNextShape(sf::RenderTexture& win);
			virtual ~ShapeDealerWidget();
		};
	}
}
#endif
