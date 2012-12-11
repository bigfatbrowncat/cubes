/*
 * AnimtedPopupsManager.cpp
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#include "AnimatedPopupsManager.h"

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	namespace controllers
	{
		AnimatedPopupsManager::AnimatedPopupsManager(float maxAge) :
				maxAge(maxAge)
		{

		}

		void AnimatedPopupsManager::popup(string text)
		{
			popups.push_back(AnimatedPopupText(text));
		}

		void AnimatedPopupsManager::processTimeStep(float dt)
		{
			for (list<AnimatedPopupText>::iterator iter = popups.begin(); iter != popups.end(); iter++)
			{
				(*iter).processTimeStep(dt);
			}

			list<AnimatedPopupText>::iterator iter = popups.begin();
			while (iter != popups.end())
			{
				if ((*iter).getAge() > maxAge)
				{
					popups.erase(iter);
				}
				iter++;
			}
		}

		AnimatedPopupsManager::~AnimatedPopupsManager()
		{

		}

	}
}
