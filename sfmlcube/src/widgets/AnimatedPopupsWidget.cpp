/*
 * AnimatedPopupsPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include <list>
#include <sstream>
#include <cmath>

#include "../controllers/AnimatedPopupLine.h"
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

		AnimatedPopupsWidget::AnimatedPopupsWidget(const AnimatedPopupsManager& animatedPopupsManager, const sf::RenderTarget& target, const sf::Font& numberFont, const sf::Font& textFont, const CubesFieldWidget& cubesFieldWidget) :
				animatedPopupsManager(animatedPopupsManager),
				target(target),
				currentPopup(animatedPopupsManager.getChainHead()),
				numberFont(numberFont), textFont(textFont),
				cubesFieldWidget(cubesFieldWidget)
		{

		}

		void AnimatedPopupsWidget::draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			for (list<AnimatedPopupTextWidget*>::const_iterator iter = popupWidgets.begin();
			     iter != popupWidgets.end();
			     iter++)
			{
				(*iter)->draw(textWithShadowPainter, target, states);
			}
		}

		void AnimatedPopupsWidget::processTimeStep(float dt)
		{
			while (currentPopup->getNext() != NULL)
			{
				const AnimatedPopupMessage& apt = *currentPopup->getPopupText();
				Shape shp = apt.getShape();

				float sourceGlobalDeltaY, destinationGlobalDeltaY;
				float sourceFullHeight = 0, destinationFullHeight = 0;

				// Calculating global delta-y
				for (list<AnimatedPopupLine>::const_iterator iter = apt.getLinesBegin(); iter != apt.getLinesEnd(); iter++)
				{
					const AnimatedPopupLine& line = *iter;

					// Calculating "size by value" multiplicator
					float effVal = line.getValue();
					if (line.getType() == AnimatedPopupLine::tLines)
					{
						effVal *= 2;
					}

					float smul = sqrt(log(effVal + 1) / log(10));

					if (line.getAnimationType() == AnimatedPopupLine::atCounter)
					{
						sourceFullHeight += 20 * smul;
						destinationFullHeight += 50 * smul;
					}
					else if (line.getAnimationType() == AnimatedPopupLine::atMessage)
					{
						sourceFullHeight += 20 * smul;
						destinationFullHeight += 30 * smul;
					}
				}

				sourceGlobalDeltaY = -sourceFullHeight / 2;
				destinationGlobalDeltaY = -destinationFullHeight / 2;

				// Laying out
				float sourceDeltaY = sourceGlobalDeltaY;
				float destinationDeltaY = destinationGlobalDeltaY;
				for (list<AnimatedPopupLine>::const_iterator iter = apt.getLinesBegin(); iter != apt.getLinesEnd(); iter++)
				{
					const AnimatedPopupLine& line = *iter;

					// Calculating "size by value" multiplier
					float effVal = line.getValue();
					if (line.getType() == AnimatedPopupLine::tLines)
					{
						effVal *= 2;
					}

					float smul = sqrt(log(effVal + 1) / log(20));

					if (line.getAnimationType() == AnimatedPopupLine::atCounter)
					{
						sourceDeltaY += 20 * smul / 2;       // half of my source size
						destinationDeltaY += 50 * smul / 2;  // half of my destination size

						AnimatedPopupTextWidget* aptwFlyAway = new AnimatedPopupTextWidget(line, target.getSize(), numberFont, textFont, cubesFieldWidget,
															0,        0 + sourceDeltaY,              20 * smul, -30,
															100 * smul, 20 * smul + destinationDeltaY, 50 * smul,  20,  2 * smul);
						popupWidgets.push_back(aptwFlyAway);
						sourceDeltaY += 20 * smul / 2;       // another half of my source size
						destinationDeltaY += 50 * smul / 2;  // another half of my destination size
					}
					else if (line.getAnimationType() == AnimatedPopupLine::atMessage)
					{
						sourceDeltaY += 20 * smul / 2;       // half of my source size
						destinationDeltaY += 30 * smul / 2;  // half of my destination size

						AnimatedPopupTextWidget* aptwZoomIn = new AnimatedPopupTextWidget(line, target.getSize(), numberFont, textFont, cubesFieldWidget,
														   0, 0 + sourceDeltaY,      20 * smul, 0,
														   0, 0 + destinationDeltaY, 30 * smul, 0, 2.5 * smul);
						popupWidgets.push_back(aptwZoomIn);

						sourceDeltaY += 20 * smul / 2;       // another half of my source size
						destinationDeltaY += 30 * smul / 2;  // another half of my destination size
					}
					else
					{
						Logger::DEFAULT.logError("Strange value of getAnimationType");
					}
				}

				currentPopup = currentPopup->getNext();
			}

			// Removing the old popups
			for (list<AnimatedPopupTextWidget*>::iterator iter = popupWidgets.begin(); iter != popupWidgets.end() && popupWidgets.size() > 0; )
			{
				if ((*iter)->isFadeOutComplete())
				{
					delete (*iter);
					popupWidgets.remove(*iter);
					iter = popupWidgets.begin();
				}
				else
					iter ++;
			}

			// Processing time step with children
			for (list<AnimatedPopupTextWidget*>::iterator iter = popupWidgets.begin();
					iter != popupWidgets.end(); iter++)
			{
				(*iter)->processTimeStep(dt);
			}
		}

		AnimatedPopupsWidget::~AnimatedPopupsWidget()
		{

		}

	}
}
