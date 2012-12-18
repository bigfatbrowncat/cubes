/*
 * AnimatedPopupTextPainter.h
 *
 *  Created on: Dec 10, 2012
 *      Author: imizus
 */

#ifndef ANIMATEDPOPUPTEXTPAINTER_H_
#define ANIMATEDPOPUPTEXTPAINTER_H_

#include <SFML/Graphics.hpp>

#include "GaussianGlowingTextPainter.h"

#include "../controllers/AnimatedPopupText.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget;

		class AnimatedPopupTextWidget
		{
		private:
			const AnimatedPopupText& apt;
			const sf::Font& font;
			const CubesFieldWidget& cubesFieldWidget;

			float sourceX, sourceY, sourceSize, sourceAngle;
			float destinationX, destinationY, destinationSize, destinationAngle;
			float fadeOutTime;

			float alpha;
			float x, y, size, angle, time;

			bool fadeOutComplete;

		public:
			AnimatedPopupTextWidget(const AnimatedPopupText& apt, const sf::Font& font, const CubesFieldWidget& cubesFieldWidget, float sourceX, float sourceY, float sourceSize, float sourceAngle,
	                  float destinationX, float destinationY, float destinationSize, float destinationAngle, float fadeOutTime);

			void processTimeStep(float dt);

			void draw(GaussianGlowingTextPainter& textWithShadowPainter, sf::RenderTarget& target, sf::RenderStates states) const;

			bool isFadeOutComplete() const { return fadeOutComplete; }
			float getAlpha() const { return alpha; }
			float getX() const { return x; }
			float getY() const { return y; }
			float getSize() const { return size; }
			float getAngle() const { return angle; }

			virtual ~AnimatedPopupTextWidget();
		};

	}
}
#endif
