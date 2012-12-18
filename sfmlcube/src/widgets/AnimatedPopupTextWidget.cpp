/*
 * AnimatedPopupTextPainter.cpp
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#include <sstream>

#include "../Logger.h"
#include "../movingcubes/Coordinates.h"
#include "../movingcubes/CubeCoordinates.h"

#include "AnimatedPopupTextWidget.h"
#include "CubesFieldWidget.h"

using namespace std;

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace widgets
	{

		AnimatedPopupTextWidget::AnimatedPopupTextWidget(const AnimatedPopupText& apt, const sf::Font& font, const CubesFieldWidget& cubesFieldWidget, float sourceX, float sourceY, float sourceSize, float sourceAngle,
                float destinationX, float destinationY, float destinationSize, float destinationAngle, float fadeOutTime) :
				apt(apt), font(font), cubesFieldWidget(cubesFieldWidget),
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
			alpha = 1.0 - d * d * d;
			x = sourceX * s + destinationX * d;
			y = sourceY * s + destinationY * d;
			size = sourceSize * s + destinationSize * d;
			angle = sourceAngle * s + destinationAngle * d;
		}

		void AnimatedPopupTextWidget::draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			float maxsize = max(sourceSize, destinationSize);

			sf::Text tx(apt.getText(), font, maxsize);

			float cx = ((float)apt.getShape().getLeft() + apt.getShape().getRight()) / 2;
			float cy = ((float)apt.getShape().getTop() + apt.getShape().getBottom()) / 2;

			CubeCoordinates shapeCenter((int)cx, (int)cy);
			Coordinates center((cx - (int)cx), -(cy - (int)cy), 0);

			Coordinates pos = cubesFieldWidget.fromCubeInShapeCoordsToFieldCoords(target, apt.getShape(), shapeCenter, center);

			if (apt.getType() == AnimatedPopupText::tScore)
			{
				tx.scale(size / maxsize, size / maxsize);
			}
			else if (apt.getType() == AnimatedPopupText::tLines)
			{
				tx.scale(2 * size / maxsize, 2 * size / maxsize);
			}
			else
			{
				Logger::DEFAULT.logError("Incorrect value of apt type");
			}

			tx.setPosition(pos.getX(), pos.getY());
			tx.move(-tx.getGlobalBounds().width + x, -tx.getGlobalBounds().height + y);

			tx.setRotation(angle);

			if (apt.getType() == AnimatedPopupText::tScore)
			{
				tx.setColor(sf::Color(192, 192, 255, alpha * 255));
			}
			else if (apt.getType() == AnimatedPopupText::tLines)
			{
				tx.setColor(sf::Color(255, 192, 192, alpha * 255));
			}
			else
			{
				Logger::DEFAULT.logError("Incorrect value of apt type");
			}

			textWithShadowPainter.drawText(tx, target, sf::Color(0, 0, 0, alpha * 255), states);
		}

		AnimatedPopupTextWidget::~AnimatedPopupTextWidget()
		{

		}

	}
}
