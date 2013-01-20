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

		AnimatedPopupTextWidget::AnimatedPopupTextWidget(const AnimatedPopupLine& apt, sf::Vector2u targetSize, const sf::Font& numberFont, const sf::Font& textFont, const CubesFieldWidget& cubesFieldWidget, float sourceX, float sourceY, float sourceSize, float sourceAngle,
                float destinationX, float destinationY, float destinationSize, float destinationAngle, float fadeOutTime) :
				apt(apt), targetSize(targetSize), numberFont(numberFont), textFont(textFont), cubesFieldWidget(cubesFieldWidget),
				sourceX(sourceX), sourceY(sourceY), sourceSize(sourceSize), sourceAngle(sourceAngle),
				destinationX(destinationX), destinationY(destinationY), destinationSize(destinationSize), destinationAngle(destinationAngle), fadeOutTime(fadeOutTime),
				alpha(1.0), x(sourceX), y(sourceY), size(sourceSize), angle(sourceAngle), time(0), fadeOutComplete(false)
		{
			const sf::Font* pf;
			maxsize = max(sourceSize, destinationSize);

			if (apt.getAnimationType() == AnimatedPopupLine::atMessage)
			{
				pf = &textFont;
			}
			else if (apt.getAnimationType() == AnimatedPopupLine::atCounter)
			{
				pf = &numberFont;
			}
			else
			{
				Logger::DEFAULT.logError("Incorrect value of animation type");
			}

			text = sf::Text(apt.getText(), *pf, maxsize);
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

			// Updating text

			text.setScale(size / maxsize, size / maxsize);

			float textWidth0 = text.findCharacterPos(-1).x - text.findCharacterPos(0).x;
			float textHeight0 = text.getCharacterSize() * text.getScale().y;
			text.setPosition(-textWidth0 / 2 + x, -textHeight0 / 2 + y);

			text.setRotation(angle);

			if (apt.getType() == AnimatedPopupLine::tScore)
			{
				text.setColor(sf::Color(192, 192, 255, alpha * 255));
			}
			else if (apt.getType() == AnimatedPopupLine::tLines)
			{
				text.setColor(sf::Color(255, 192, 192, alpha * 255));
			}
			else
			{
				Logger::DEFAULT.logError("Incorrect value of apt type");
			}

			float cx = ((float)apt.getMessage().getShape().getLeft() + apt.getMessage().getShape().getRight()) / 2;
			float cy = ((float)apt.getMessage().getShape().getTop() + apt.getMessage().getShape().getBottom()) / 2;

			CubeCoordinates shapeCenter((int)cx, (int)cy);
			Coordinates center((cx - (int)cx), -(cy - (int)cy), 0);

			Coordinates pos = cubesFieldWidget.fromCubeInShapeCoordsToFieldCoords(targetSize, apt.getMessage().getShape(), shapeCenter, center);
			text.move(pos.getX(), pos.getY());

		}

		void AnimatedPopupTextWidget::draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			textWithShadowPainter.drawText(text, target, sf::Color(0, 0, 0, alpha * 255), states);
		}

		AnimatedPopupTextWidget::~AnimatedPopupTextWidget()
		{
			//delete text;
		}

	}
}
