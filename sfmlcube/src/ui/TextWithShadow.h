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
	namespace ui
	{
		class TextWithShadow : public sf::Drawable
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

			sf::Text text;
			float shadowWidth;
			float margin;
			sf::FloatRect realBounds;

			void initTexturesAndSprites();
			void updateTexturesAndSprites();
			void freeTexturesAndSprites();
			void updateRealBounds();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		public:
			TextWithShadow();
			void setText(const sf::Text& text);
			void setShadowWidth(float value) { shadowWidth = value; margin = 2 * shadowWidth; }

			virtual ~TextWithShadow();
		};
	}
}
#endif