/*
 * AnimatedPopupsPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include <list>
#include <sstream>

#include "../controllers/AnimatedPopupText.h"
#include "../controllers/AnimatedPopupsManager.h"

#include "../Logger.h"

#include "AnimatedPopupsWidget.h"

using namespace std;

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{

		AnimatedPopupsWidget::AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& font) :
				animatedPopupsManager(animatedPopupsManager),
				currentPopup(animatedPopupsManager.getChainHead()),
				font(font)
		{

		}

		void AnimatedPopupsWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.pushGLStates();
			for (map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget>::const_iterator iter = popupWidgets.begin();
			     iter != popupWidgets.end();
			     iter++)
			{
				target.draw((*iter).second, states);
			}
			target.popGLStates();
		}

		void AnimatedPopupsWidget::processTimeStep(float dt)
		{
			while (currentPopup->getNext() != NULL)
			{
				Logger::DEFAULT.logInfo("add");
				const AnimatedPopupText& apt = *currentPopup->getPopupText();
				AnimatedPopupTextWidget aptw(apt, font, 0, 0, 10, 0, 200, 100, 50, 30, 3);
				std::pair<const AnimatedPopupChainLink*, AnimatedPopupTextWidget> newPair(currentPopup, aptw);
				popupWidgets.insert(newPair);
				currentPopup = currentPopup->getNext();
			}

			// Removing the old popups
			for (map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin(); iter != popupWidgets.end() && popupWidgets.size() > 0; )
			{
				if ((*iter).second.isFadeOutComplete())
				{
					popupWidgets.erase(iter++);
				}
				else
					iter ++;
			}

			// Processing time step with children
			for (map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin();
					iter != popupWidgets.end(); iter++)
			{
				(*iter).second.processTimeStep(dt);
			}
		}

		AnimatedPopupsWidget::~AnimatedPopupsWidget()
		{

		}

	}
}
