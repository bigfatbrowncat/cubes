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
		sf::FloatRect realBounds;

		void initTexturesAndSprites();
		void updateTexturesAndSprites();
		void freeTexturesAndSprites();
		void updateRealBounds();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	public:
		TextWithShadow();
		void setText(const sf::Text& text);
		void setShadowWidth(float value) { shadowWidth = value; }

		virtual ~TextWithShadow();
	};

}
#endif
