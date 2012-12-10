/*
 * AnimtedPopupsManager.h
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#ifndef ANIMTEDPOPUPSMANAGER_H_
#define ANIMTEDPOPUPSMANAGER_H_

#include <list>

#include <SFML/Graphics.hpp>

#include "AnimatedPopupText.h"

using namespace std;

namespace sfmlcubes
{
	namespace widgets
	{

		class AnimtedPopupsManager : public sf::Drawable
		{
		private:
			list<AnimatedPopupText> popups;
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:

			AnimtedPopupsManager();
			void processTimeStep(float dt);
			virtual ~AnimtedPopupsManager();
		};

	}
}
#endif
