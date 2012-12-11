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
	namespace controllers
	{

		class AnimatedPopupsManager
		{
		private:
			float maxAge;
			list<AnimatedPopupText> popups;
		public:
			AnimatedPopupsManager(float maxAge);
			void popup(string text);
			void processTimeStep(float dt);
			const list<AnimatedPopupText>& getPopups() const { return popups; }

			virtual ~AnimatedPopupsManager();
		};

	}
}
#endif
