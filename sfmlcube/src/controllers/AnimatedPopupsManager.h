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

#include "AnimatedPopupMessage.h"

using namespace std;

namespace sfmlcubes
{
	namespace controllers
	{
		class AnimatedPopupsManager;

		class AnimatedPopupChainLink
		{
			friend class AnimatedPopupsManager;
		private:
			AnimatedPopupChainLink* next;
			AnimatedPopupMessage* popupText;
		public:
			AnimatedPopupChainLink(AnimatedPopupChainLink* next, AnimatedPopupMessage* text) :
				next(next), popupText(text)
			{}
			const AnimatedPopupChainLink* getNext() const { return next; }
			const AnimatedPopupMessage* getPopupText() const { return popupText; }
		};

		class AnimatedPopupsManager
		{
		private:
			AnimatedPopupChainLink* chainHead;
			AnimatedPopupChainLink* chainTail;

		public:
			AnimatedPopupsManager();
			void popup(const AnimatedPopupMessage& message);
			const AnimatedPopupChainLink* getChainHead() const { return chainHead; }

			virtual ~AnimatedPopupsManager();
		};
	}
}
#endif
