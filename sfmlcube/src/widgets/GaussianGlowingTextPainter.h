/*
 * TextWithShadow.h
 *
 *  Created on: Dec 5, 2012
 *      Author: imizus
 */

#ifndef TEXTWITHSHADOW_H_
#define TEXTWITHSHADOW_H_

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	namespace widgets
	{
		class GaussianGlowingTextPainter
		{
		private:
			static sf::Shader** shadowShaders;
			static sf::RenderStates** shadowRenderStates;
		public:
			static void initialize();
			static void finalize();
		private:
			sf::RenderTexture** textures;
			sf::Sprite** sprites;

			float shadowWidth;
			float margin;
			sf::FloatRect realBounds;

			void initTexturesAndSprites(const sf::Text& text);
			void updateTexturesAndSprites(const sf::Text& text);
			void freeTexturesAndSprites();

		public:
			GaussianGlowingTextPainter();

			virtual void drawText(const sf::Text& text, sf::RenderTarget& target, const sf::Color& glowingColor, sf::RenderStates states);

			void setShadowWidth(float value) { shadowWidth = value; margin = 2 * shadowWidth; }

			virtual ~GaussianGlowingTextPainter();
		};
	}
}
#endif
