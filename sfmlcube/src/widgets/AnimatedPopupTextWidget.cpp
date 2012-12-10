/*
 * AnimatedPopupTextPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include "AnimatedPopupTextWidget.h"

namespace sfmlcubes
{
	namespace widgets
	{

		AnimatedPopupTextWidget::AnimatedPopupTextWidget(const AnimatedPopupText& apt, const sf::Font& font, float sourceX, float sourceY, float sourceSize, float sourceAngle,
                float destinationX, float destinationY, float destinationSize, float destinationAngle, float fadeOutTime) :
				apt(apt), font(font),
				sourceX(sourceX), sourceY(sourceY), sourceSize(sourceSize), sourceAngle(sourceAngle),
				destinationX(destinationX), destinationY(destinationY), destinationSize(destinationSize), destinationAngle(destinationAngle), fadeOutTime(fadeOutTime),
				alpha(1.0), x(sourceX), y(sourceY), size(sourceSize), angle(sourceAngle), time(0), fadeOutComplete(false)
		{

		}

		void AnimatedPopupTextWidget::processTimeStep(float dt)
		{
			time += dt;

			if (time > fadeOutTime)
			{
				time = fadeOutTime;
				fadeOutComplete = true;
			}

			float d = time / fadeOutTime;
			float s = 1 - d;
			alpha = 1.0 - d * d;
			x = sourceX * s + destinationX * d;
			y = sourceY * s + destinationY * d;
			size = sourceSize * s + destinationSize * d;
			angle = sourceAngle * s + destinationAngle * d;
		}

		void AnimatedPopupTextWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			sf::Text tx(apt.getText(), font, size);
			tx.setPosition(x, y);
			tx.setRotation(angle);
			tx.setColor(sf::Color(255, 255, 255, alpha * 255));

			target.draw(tx, states);
		}

		AnimatedPopupTextWidget::~AnimatedPopupTextWidget()
		{

		}

	}
}
