/*
 * AnimatedPopupText.h
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#ifndef ANIMATEDPOPUPTEXT_H_
#define ANIMATEDPOPUPTEXT_H_

#include <string>

#include <SFML/Graphics.hpp>

using namespace std;

namespace sfmlcubes
{
	namespace widgets
	{

		class AnimatedPopupText : public sf::Drawable
		{
		private:
			string text;

			const sf::Font& font;

			float sourceX, sourceY, sourceSize, sourceAngle;
			float destinationX, destinationY, destinationSize, destinationAngle;
			float fadeOutTime;

			float alpha;
			float x, y, size, angle, time;

			bool fadeOutComplete;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		public:
			AnimatedPopupText(string text, const sf::Font& font, float sourceX, float sourceY, float sourceSize, float sourceAngle,
			                  float destinationX, float destinationY, float destinationSize, float destinationAngle, float fadeOutTime);

			void processTimeStep(float dt);
			bool isFadeOutComplete() { return fadeOutComplete; }

			virtual ~AnimatedPopupText();
		};

	}
}
#endif
