/*
 * AnimatedPopupsPainter.h
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#ifndef ANIMATEDPOPUPSPAINTER_H_
#define ANIMATEDPOPUPSPAINTER_H_

#include <map>
#include <SFML/Graphics.hpp>

#include "AnimatedPopupTextWidget.h"
#include "GaussianGlowingTextPainter.h"
#include "../controllers/AnimatedPopupsManager.h"

using namespace std;

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget;

		class AnimatedPopupsWidget
		{
		private:
			const AnimatedPopupsManager& animatedPopupsManager;
			const AnimatedPopupChainLink* currentPopup;
			map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget> popupWidgets;
			const sf::Font& numberFont;
			const sf::Font& textFont;
			const CubesFieldWidget& cubesFieldWidget;

		public:
			AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& numberFont, const sf::Font& textFont, const CubesFieldWidget& cubesFieldWidget);

			void draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const;
			void processTimeStep(float dt);

			virtual ~AnimatedPopupsWidget();
		};

	}
}
#endif
