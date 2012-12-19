/*
 * TextWithShadowPainter.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: imizus
 */

#include <sstream>

#include "../sfmlcubes.h"
#include "../Logger.h"

#include "GaussianGlowingTextPainter.h"

using namespace sf;
using namespace std;

namespace sfmlcubes
{
	namespace widgets
	{
		sf::Shader** GaussianGlowingTextPainter::shadowShaders;
		sf::RenderStates** GaussianGlowingTextPainter::shadowRenderStates;

		void GaussianGlowingTextPainter::initialize()
		{
			shadowRenderStates = new sf::RenderStates*[2];
			shadowShaders = new sf::Shader*[2];

			shadowShaders[0] = new sf::Shader;
			shadowRenderStates[0] = new sf::RenderStates;
			if (shadowShaders[0]->loadFromFile(api->locateResource("res", "trivial.vert"), api->locateResource("res", "GaussianGlowingText.frag")))
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
			if (shadowShaders[1]->loadFromFile(api->locateResource("res", "trivial.vert"), api->locateResource("res", "GaussianGlowingText.frag")))
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

		void GaussianGlowingTextPainter::finalize()
		{
			delete shadowShaders[0];
			delete shadowShaders[1];
			delete [] shadowShaders;
		}

		void GaussianGlowingTextPainter::initTexturesAndSprites(const Text& text)
		{
			textures = new RenderTexture*[2];
			sprites = new Sprite*[2];

			textures[0] = textures[1] = 0;
			sprites[0] = sprites[1] = 0;

			realBounds = text.getGlobalBounds();

			if (text.getGlobalBounds().width + 2 * margin > realBounds.width)
				realBounds.width = text.getGlobalBounds().width + 2 * margin;
			if (text.getGlobalBounds().height + 2 * margin > realBounds.height)
				realBounds.height = text.getGlobalBounds().height + 2 * margin;

			realBounds.width *= 2;
			realBounds.height *= 2;

			//realBounds.width = text.findCharacterPos(0).x + text.findCharacterPos(-1).x;
			//realBounds.height = text.findCharacterPos(0).y + text.findCharacterPos(-1).y;

			if (realBounds.width > 0 && realBounds.height > 0)
			{
				textures[0] = new RenderTexture;
				textures[0]->create(realBounds.width, realBounds.height, false);
				textures[1] = new RenderTexture;
				textures[1]->create(realBounds.width, realBounds.height, false);
				sprites[0] = new Sprite;
				sprites[0]->setTexture(textures[0]->getTexture(), true);
				sprites[1] = new Sprite;
				sprites[1]->setTexture(textures[1]->getTexture(), true);
			}
		}

		void GaussianGlowingTextPainter::updateTexturesAndSprites(const Text& text)
		{
			if (text.getGlobalBounds().width + 2 * margin > realBounds.width ||
				text.getGlobalBounds().height + 2 * margin > realBounds.height)
			{
				freeTexturesAndSprites();
				initTexturesAndSprites(text);
			}
		}

		void GaussianGlowingTextPainter::freeTexturesAndSprites()
		{
			if (textures != NULL || sprites != NULL)
			{
				delete textures[0];
				delete textures[1];
				delete sprites[0];
				delete sprites[1];
				delete [] textures; textures = NULL;
				delete [] sprites; sprites = NULL;
			}
		}

		GaussianGlowingTextPainter::GaussianGlowingTextPainter() :
				textures(NULL), sprites(NULL),
				shadowWidth(6),
				margin(0),
				realBounds(0, 0, 0, 0)
		{

		}

		void GaussianGlowingTextPainter::drawText(const Text& text, RenderTarget& target, const Color& glowingColor, RenderStates states)
		{
			updateTexturesAndSprites(text);
			if (realBounds.width > 0 && realBounds.height > 0)
			{
				Text t(text);
				t.setPosition(margin, margin);
				RenderStates rs[2];

				shadowShaders[0]->setParameter("blur_radius", (float)shadowWidth);
				shadowShaders[0]->setParameter("glowing_color", (float)glowingColor.r / 255, (float)glowingColor.g / 255, (float)glowingColor.b / 255, (float)glowingColor.a / 255);
				shadowShaders[0]->setParameter("glowing_pressure", (float)(1.2f));
				shadowShaders[0]->setParameter("screen_width", realBounds.width);
				shadowShaders[0]->setParameter("screen_height", realBounds.height);
				rs[0].shader = shadowShaders[0];

				shadowShaders[1]->setParameter("blur_radius", (float)shadowWidth);
				shadowShaders[1]->setParameter("glowing_color", (float)glowingColor.r / 255, (float)glowingColor.g / 255, (float)glowingColor.b / 255, (float)glowingColor.a / 255);
				shadowShaders[1]->setParameter("glowing_pressure", (float)(1.2f));
				shadowShaders[1]->setParameter("screen_width", realBounds.width);
				shadowShaders[1]->setParameter("screen_height", realBounds.height);
				rs[1].shader = shadowShaders[1];

				// Drawing the first layer to the second one
				textures[0]->clear(sf::Color(0, 0, 0, 0));
				textures[0]->draw(t, RenderStates::Default);
				textures[0]->display();

				// Drawing the first layer to the second one
				textures[1]->clear(sf::Color(0, 0, 0, 0));
				textures[1]->draw(*(sprites[0]), rs[0]);
				textures[1]->display();

				sprites[1]->setPosition(text.getPosition().x - margin,
										text.getPosition().y - margin);

				target.pushGLStates();
				target.draw(*(sprites[1]), rs[1]);
				target.popGLStates();

				target.pushGLStates();
				target.draw(text, states);
				target.popGLStates();
			}

		}


		GaussianGlowingTextPainter::~GaussianGlowingTextPainter()
		{
			freeTexturesAndSprites();
		}
	}
}
