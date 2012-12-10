/*
 * AnimatedPopupsPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include <list>

#include "../controllers/AnimatedPopupText.h"
#include "../controllers/AnimatedPopupsManager.h"

#include "AnimatedPopupsWidget.h"

using namespace std;

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{

		AnimatedPopupsWidget::AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& font) :
				animatedPopupsManager(animatedPopupsManager), font(font)
		{

		}

		void AnimatedPopupsWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (map<const AnimatedPopupText*, AnimatedPopupTextWidget>::const_iterator iter = popupWidgets.begin();
			     iter != popupWidgets.end();
			     iter++)
			{
				target.draw((*iter).second, states);
			}
		}

		void AnimatedPopupsWidget::processTimeStep(float dt)
		{
			// Adding widgets for the new popups
			for (list<AnimatedPopupText>::const_iterator iter = animatedPopupsManager.getPopups().begin();
			     iter != animatedPopupsManager.getPopups().end(); iter++)
			{
				if (popupWidgets.find(&(*iter)) == popupWidgets.end())
				{
					AnimatedPopupTextWidget aptw(*iter, font, 0, 0, 10, 0, 200, 100, 50, 30, 3);
					std::pair<const AnimatedPopupText*, AnimatedPopupTextWidget> newPair(&(*iter), aptw);
					popupWidgets.insert(newPair);
				}
			}

			// Removing the old popups
			map<const AnimatedPopupText*, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin();
			while (iter != popupWidgets.end())
			{
				if ((*iter).second.isFadeOutComplete())
				{
					popupWidgets.erase(iter);
				}
				iter ++;
			}

			// Processing time step with children
			for (map<const AnimatedPopupText*, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin();
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
