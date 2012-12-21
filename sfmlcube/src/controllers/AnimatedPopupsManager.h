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
		class AnimatedPopupsManager;

		class AnimatedPopupChainLink
		{
			friend class AnimatedPopupsManager;
		private:
			AnimatedPopupChainLink* next;
			AnimatedPopupText* popupText;
		public:
			AnimatedPopupChainLink(AnimatedPopupChainLink* next, AnimatedPopupText* text) :
				next(next), popupText(text)
			{}
			const AnimatedPopupChainLink* getNext() const { return next; }
			const AnimatedPopupText* getPopupText() const { return popupText; }
		};

		class AnimatedPopupsManager
		{
		private:
			AnimatedPopupChainLink* chainHead;
			AnimatedPopupChainLink* chainTail;

		public:
			AnimatedPopupsManager();
			void popup(string text, int value, AnimatedPopupText::Type type, AnimatedPopupText::AnimationType animationType, const Shape& shape);
			const AnimatedPopupChainLink* getChainHead() const { return chainHead; }

			virtual ~AnimatedPopupsManager();
		};
	}
}
#endif
