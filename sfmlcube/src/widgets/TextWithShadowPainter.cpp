/*
 * TextWithShadowPainter.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: imizus
 */

#include "../sfmlcubes.h"
#include "../Logger.h"

#include "TextWithShadowPainter.h"

using namespace sf;

namespace sfmlcubes
{
	namespace widgets
	{
		sf::Shader** TextWithShadowPainter::shadowShaders;
		sf::RenderStates** TextWithShadowPainter::shadowRenderStates;

		void TextWithShadowPainter::initialize()
		{
			shadowRenderStates = new sf::RenderStates*[2];
			shadowShaders = new sf::Shader*[2];

			shadowShaders[0] = new sf::Shader;
			shadowRenderStates[0] = new sf::RenderStates;
			if (shadowShaders[0]->loadFromFile(api->locateResource("res", "trivial.vert"), api->locateResource("res", "ui_shadows.frag")))
			{
				shadowRenderStates[0]->shader = shadowShaders[0];
				shadowShaders[0]->setParameter("texture", sf::Shader::CurrentTexture);
				shadowShaders[0]->setParameter("blur_vector", 1.f, 0.f);
			}
			else
			{
				Logger::DEFAULT.logError("Can't load UI shadows shader.");
			}

			shadowShaders[1] = new sf::Shader;
			shadowRenderStates[1] = new sf::RenderStates;
			if (shadowShaders[1]->loadFromFile(api->locateResource("res", "trivial.vert"), api->locateResource("res", "ui_shadows.frag")))
			{
				shadowRenderStates[1]->shader = shadowShaders[1];
				shadowShaders[1]->setParameter("texture", sf::Shader::CurrentTexture);
				shadowShaders[1]->setParameter("blur_vector", 0.f, 1.f);
			}
			else
			{
				Logger::DEFAULT.logError("Can't load UI shadows shader.");
			}

		}

		void TextWithShadowPainter::finalize()
		{
			delete shadowShaders[0];
			delete shadowShaders[1];
			delete [] shadowShaders;
		}

		void TextWithShadowPainter::updateRealBounds(const Text& text)
		{
			realBounds = text.getGlobalBounds();
			// This is experimental. I don't know why adding 2*margin is not enough
			realBounds.width *= 2;
			realBounds.height *= 2;
		}

		void TextWithShadowPainter::initTexturesAndSprites(const Text& text)
		{
			textures = new RenderTexture*[2];
			sprites = new Sprite*[2];

			textures[0] = textures[1] = 0;
			sprites[0] = sprites[1] = 0;

			updateRealBounds(text);

			if (realBounds.width > 0 && realBounds.height > 0)
			{
				textures[0] = new RenderTexture;
				textures[0]->create(realBounds.width, realBounds.height, true);
				textures[1] = new RenderTexture;
				textures[1]->create(realBounds.width, realBounds.height, true);
				sprites[0] = new Sprite;
				sprites[0]->setTexture(textures[0]->getTexture(), true);
				sprites[1] = new Sprite;
				sprites[1]->setTexture(textures[1]->getTexture(), true);
			}
		}

		void TextWithShadowPainter::updateTexturesAndSprites(const Text& text)
		{
			if (text.getGlobalBounds().width > realBounds.width ||
				text.getGlobalBounds().height > realBounds.height)
			{
				if (textures != NULL || sprites != NULL)
				{
					freeTexturesAndSprites();
				}
				initTexturesAndSprites(text);
			}
		}

		void TextWithShadowPainter::freeTexturesAndSprites()
		{
			delete textures[0];
			delete textures[1];
			delete sprites[0];
			delete sprites[1];
			delete [] textures; textures = NULL;
			delete [] sprites; sprites = NULL;
		}

		TextWithShadowPainter::TextWithShadowPainter() :
				textures(NULL), sprites(NULL),
				shadowWidth(5),
				margin(0),
				realBounds(0, 0, 0, 0)
		{

		}

		void TextWithShadowPainter::drawText(const Text& text, RenderTarget& target, RenderStates states)
		{
			updateTexturesAndSprites(text);
			if (realBounds.width > 0 && realBounds.height > 0)
			{
				Text t(text);
				t.setPosition(margin, -text.getGlobalBounds().height / 2 + margin);
				RenderStates rs[2];

				shadowShaders[0]->setParameter("blur_radius", (float)shadowWidth);
				shadowShaders[0]->setParameter("shadow_pressure", (float)(1.2f));
				shadowShaders[0]->setParameter("screen_width", realBounds.width);
				shadowShaders[0]->setParameter("screen_height", realBounds.height);
				rs[0].shader = shadowShaders[0];

				shadowShaders[1]->setParameter("blur_radius", (float)shadowWidth);
				shadowShaders[1]->setParameter("shadow_pressure", (float)(1.2f));
				shadowShaders[1]->setParameter("screen_width", realBounds.width);
				shadowShaders[1]->setParameter("screen_height", realBounds.height);
				rs[1].shader = shadowShaders[1];

				// Drawing the first layer to the second one
				textures[0]->clear(sf::Color(0, 0, 0, 0));
				textures[0]->draw(t, RenderStates::Default);
				textures[0]->display();

				textures[1]->clear(sf::Color(0, 0, 0, 0));
				// Drawing the first layer to the second one
				textures[1]->draw(*(sprites[0]), rs[0]);
				textures[1]->display();


				sprites[1]->setPosition(text.getPosition().x - margin,
										text.getPosition().y - margin + text.getGlobalBounds().height / 2);
				target.draw(*(sprites[1]), rs[1]);
				target.draw(text, states);
			}
		}


		TextWithShadowPainter::~TextWithShadowPainter()
		{
			freeTexturesAndSprites();
		}
	}
}
