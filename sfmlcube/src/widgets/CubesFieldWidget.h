/*
 * CubesFieldWidget.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CUBESFIELDWIDGET_H_
#define CUBESFIELDWIDGET_H_

#include "../controllers/CubesField.h"
#include "AnimatedPopupsWidget.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget
		{
		private:
			const CubesField& cubesField;
			AnimatedPopupsWidget animatedPopupsPainter;

			void setPerspective();
		public:
			CubesFieldWidget(const CubesField& cubesField, const sf::Font& font);
			void drawBoard(sf::RenderTarget& target);
			void processTimeStep(float dt) { animatedPopupsPainter.processTimeStep(dt); }
			virtual ~CubesFieldWidget();
		};
	}
}
#endif
