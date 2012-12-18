/*
 * AnimtedPopupsManager.cpp
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#include "AnimatedPopupsManager.h"

#include <SFML/Graphics.hpp>
#include "../Logger.h"

namespace sfmlcubes
{
	namespace controllers
	{
		AnimatedPopupsManager::AnimatedPopupsManager()
		{
			chainHead = new AnimatedPopupChainLink(NULL, NULL);
			chainTail = chainHead;
		}

		void AnimatedPopupsManager::popup(string text, int value, const Shape& shape)
		{
			Logger::DEFAULT.logInfo("popup");
			chainTail->popupText = new AnimatedPopupText(text, value, shape);
			chainTail->next = new AnimatedPopupChainLink(NULL, NULL);
			chainTail = chainTail->next;
		}

		AnimatedPopupsManager::~AnimatedPopupsManager()
		{
			AnimatedPopupChainLink* iter = chainHead;
			while (iter != NULL)
			{
				AnimatedPopupChainLink* cur = iter;
				iter = iter->next;
				if (cur->popupText != NULL) delete cur->popupText;
				delete cur;
			}
			delete chainTail;
		}

	}
}
