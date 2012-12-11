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
		class AnimatedPopupsWidget : public sf::Drawable
		{
		private:
			const AnimatedPopupsManager& animatedPopupsManager;
			map<AnimatedPopupText, AnimatedPopupTextWidget> popupWidgets;
			const sf::Font& font;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:
			AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& font);

			void processTimeStep(float dt);

			virtual ~AnimatedPopupsWidget();
		};

	}
}
#endif
