/*
 * AnimtedPopupsManager.cpp
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#include "AnimtedPopupsManager.h"

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	namespace widgets
	{
		void AnimtedPopupsManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (list<AnimatedPopupText>::const_iterator iter = popups.begin(); iter != popups.end(); iter++)
			{
				target.draw(*iter, states);
			}
		}

		AnimtedPopupsManager::AnimtedPopupsManager()
		{

		}

		void AnimtedPopupsManager::processTimeStep(float dt)
		{
			for (list<AnimatedPopupText>::iterator iter = popups.begin(); iter != popups.end(); iter++)
			{
				(*iter).processTimeStep(dt);
			}
		}

		AnimtedPopupsManager::~AnimtedPopupsManager()
		{

		}

	}
}
