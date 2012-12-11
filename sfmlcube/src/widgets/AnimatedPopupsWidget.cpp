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
				animatedPopupsManager(animatedPopupsManager), font(font)
		{

		}

		void AnimatedPopupsWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (map<AnimatedPopupText, AnimatedPopupTextWidget>::const_iterator iter = popupWidgets.begin();
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
				if (popupWidgets.find(*iter) == popupWidgets.end())
				{
					AnimatedPopupTextWidget aptw(*iter, font, 0, 0, 10, 0, 200, 100, 50, 30, 3);
					std::pair<AnimatedPopupText, AnimatedPopupTextWidget> newPair(*iter, aptw);
					{
						stringstream ss;
						ss << "before insert" << popupWidgets.size();
						Logger::DEFAULT.logInfo(ss.str());
					}
					popupWidgets.insert(newPair);
				}
			}

			// Removing the old popups
			for (map<AnimatedPopupText, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin(); iter != popupWidgets.end() && popupWidgets.size() > 0; )
			{
				if ((*iter).second.isFadeOutComplete())
				{
					{
						stringstream ss;
						ss << "before erasing" << popupWidgets.size();
						Logger::DEFAULT.logInfo(ss.str());
					}
					popupWidgets.erase(iter++);
					{
						stringstream ss;
						ss << "after erasing" << popupWidgets.size();
						Logger::DEFAULT.logInfo(ss.str());
					}
				}
				else
					iter ++;
			}

			// Processing time step with children
			for (map<AnimatedPopupText, AnimatedPopupTextWidget>::iterator iter = popupWidgets.begin();
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
