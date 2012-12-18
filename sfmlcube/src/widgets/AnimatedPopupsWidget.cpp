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

		AnimatedPopupsWidget::AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::Font& font, const CubesFieldWidget& cubesFieldWidget) :
				animatedPopupsManager(animatedPopupsManager),
				currentPopup(animatedPopupsManager.getChainHead()),
				font(font),
				cubesFieldWidget(cubesFieldWidget)
		{

		}

		void AnimatedPopupsWidget::draw(TextWithShadowPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.pushGLStates();
			for (map<const AnimatedPopupChainLink*, AnimatedPopupTextWidget>::const_iterator iter = popupWidgets.begin();
			     iter != popupWidgets.end();
			     iter++)
			{
				(*iter).second.draw(textWithShadowPainter, target, states);
			}
			target.popGLStates();
		}

		void AnimatedPopupsWidget::processTimeStep(float dt)
		{
			while (currentPopup->getNext() != NULL)
			{
				const AnimatedPopupText& apt = *currentPopup->getPopupText();
				Shape shp = apt.getShape();

				// Calculating "size by value" multiplicator
				float smul = sqrt(log(apt.getValue() + 1) / log(10));

				AnimatedPopupTextWidget aptw(
						apt, font, cubesFieldWidget, 0, 0, 30 * smul, -30,
						                             200 * smul, -20, 100 * smul, 20, 1.5 * smul);
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
