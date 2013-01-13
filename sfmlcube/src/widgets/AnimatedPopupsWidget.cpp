/*
 * AnimatedPopupsPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include <list>
#include <sstream>
#include <cmath>

#include "../controllers/AnimatedPopupText.h"
#include "../controllers/AnimatedPopupsManager.h"
#include "../movingcubes/Shape.h"

#include "../Logger.h"

#include "AnimatedPopupsWidget.h"

using namespace std;

namespace sfmlcubes
{
	using namespace controllers;
	using namespace movingcubes;

	namespace widgets
	{

		AnimatedPopupsWidget::AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& numberFont, const sf::Font& textFont, const CubesFieldWidget& cubesFieldWidget) :
				animatedPopupsManager(animatedPopupsManager),
				currentPopup(animatedPopupsManager.getChainHead()),
				numberFont(numberFont), textFont(textFont),
				cubesFieldWidget(cubesFieldWidget)
		{

		}

		void AnimatedPopupsWidget::draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget>::const_iterator iter = popupWidgets.begin();
			     iter != popupWidgets.end();
			     iter++)
			{
				//target.pushGLStates();
				(*iter).second.draw(textWithShadowPainter, target, states);
				//target.popGLStates();
			}
		}

		void AnimatedPopupsWidget::processTimeStep(float dt)
		{
			while (currentPopup->getNext() != NULL)
			{
				const AnimatedPopupText& apt = *currentPopup->getPopupText();
				Shape shp = apt.getShape();

				// Calculating "size by value" multiplicator
				float effVal = apt.getValue();
				if (apt.getType() == AnimatedPopupText::tLines)
				{
					effVal *= 2;
				}

				float smul = sqrt(log(effVal + 1) / log(10));



				if (apt.getAnimationType() == AnimatedPopupText::atBonusCounter)
				{
					AnimatedPopupTextWidget aptwFlyAway(apt, numberFont, textFont, cubesFieldWidget,
					                                    0,          0,         20 * smul, -30,
					                                    100 * smul, 20 * smul, 50 * smul,  20,  2 * smul);
					std::pair<const AnimatedPopupChainLink*, AnimatedPopupTextWidget> newPair(currentPopup, aptwFlyAway);
					popupWidgets.insert(newPair);
				}
				else if (apt.getAnimationType() == AnimatedPopupText::atTextMessage)
				{
					AnimatedPopupTextWidget aptwZoomIn(apt, numberFont, textFont, cubesFieldWidget,
					                                   0, 0, 20 * smul, 0,
					                                   0, 0, 30 * smul, 0, 2.5 * smul);
					std::pair<const AnimatedPopupChainLink*, AnimatedPopupTextWidget> newPair(currentPopup, aptwZoomIn);
					popupWidgets.insert(newPair);
				}
				else
				{
					Logger::DEFAULT.logError("Strange value of getAnimationType");
				}

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
