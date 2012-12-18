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
			alpha = 1.0 - d * d;
			x = sourceX * s + destinationX * d;
			y = sourceY * s + destinationY * d;
			size = sourceSize * s + destinationSize * d;
			angle = sourceAngle * s + destinationAngle * d;
		}

		void AnimatedPopupTextWidget::draw(TextWithShadowPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const
		{
			sf::Text tx(apt.getText(), font, size);

			CubeCoordinates shapeCenter(apt.getShape().rotatingCenterX, apt.getShape().rotatingCenterY);
			Coordinates center;
			if (apt.getShape().rotatingCenterType == rctCorner)
			{
				center = Coordinates(-0.5, 0.5, 0);
			}

			Coordinates pos = cubesFieldWidget.fromCubeInShapeCoordsToFieldCoords(target, apt.getShape(), shapeCenter, center);

			tx.setPosition(pos.getX(), pos.getY());
			tx.move( - tx.getGlobalBounds().width + x,  - tx.getGlobalBounds().height + y);
			stringstream ss;
			ss << tx.getGlobalBounds().width << ", " << tx.getGlobalBounds().height;
			Logger::DEFAULT.logInfo(ss.str());

			tx.setRotation(angle);

			tx.setColor(sf::Color(192, 192, 255, alpha * 255));

			textWithShadowPainter.drawText(tx, target, states);
		}

		AnimatedPopupTextWidget::~AnimatedPopupTextWidget()
		{

		}

	}
}
