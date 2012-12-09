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
		class TextWithShadowPainter
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
			void updateRealBounds(const sf::Text& text);

		public:
			TextWithShadowPainter();

			virtual void drawText(const sf::Text& text, sf::RenderTarget& target, sf::RenderStates states);

			void setShadowWidth(float value) { shadowWidth = value; margin = 2 * shadowWidth; }

			virtual ~TextWithShadowPainter();
		};
	}
}
#endif
