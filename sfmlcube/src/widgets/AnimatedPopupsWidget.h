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
#include "../controllers/AnimatedPopupsManager.h"

using namespace std;

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget;

		class AnimatedPopupsWidget : public sf::Drawable
		{
		private:
			const AnimatedPopupsManager& animatedPopupsManager;
			const AnimatedPopupChainLink* currentPopup;
			map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget> popupWidgets;
			const sf::Font& font;
			const CubesFieldWidget& cubesFieldWidget;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:
			AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& font, const CubesFieldWidget& cubesFieldWidget);

			void processTimeStep(float dt);

			virtual ~AnimatedPopupsWidget();
		};

	}
}
#endif
