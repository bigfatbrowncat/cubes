/*
 * ClassicGame.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CLASSICGAME_H_
#define CLASSICGAME_H_

#include <SFML/Graphics.hpp>

#include "../CubesMechanic.h"
#include "TextWithShadow.h"

namespace sfmlcubes
{
	namespace ui
	{
		class ClassicGame
		{
		private:
			sf::RenderWindow& mainWindow;
			const sf::Font& textFont;
			const sf::Font& textHeavyFont;
			const sf::Font& counterFont;

			sf::RenderTexture* mainWindowTexture;
			sf::Sprite* mainWindowSprite;
			sf::Shader* mainWindowShader;
			sf::RenderStates* mainWindowRS;

			sf::Text* pauseText;
			sf::Text* gameOverText;
			sf::Text* linesFiredText;
			sf::Text* linesFiredValueText;
			sf::Text* scoreText;
			sf::Text* scoreValueText;
			sf::Text* speedText;
			sf::Text* speedValueText;
			sf::Text* nextShapeText;

			TextWithShadow* pauseTextWithShadow;
			TextWithShadow* gameOverTextWithShadow;
			TextWithShadow* linesFiredTextWithShadow;
			TextWithShadow* linesFiredValueTextWithShadow;
			TextWithShadow* scoreTextWithShadow;
			TextWithShadow* scoreValueTextWithShadow;
			TextWithShadow* speedTextWithShadow;
			TextWithShadow* speedValueTextWithShadow;
			TextWithShadow* nextShapeTextWithShadow;

			CubesMechanic board;//(12, 21);

			bool rightKeyPressed = false,
			     leftKeyPressed = false,
			     downKeyPressed = false,
			     rotateCWKeyPressed = false;

			void initLayers();
			void updateStaticText(sf::RenderTarget& win);
			void updateDynamicText(sf::RenderTarget& win);
			void drawText(sf::RenderTarget& win, sf::RenderStates rs);
			void setPerspective();
			void setView();
			void prepareScene();
			void drawBoard();
			void drawNextShape(sf::RenderTexture& win);
			void drawScene(sf::RenderTexture& win);

		public:
			ClassicGame(sf::RenderWindow& mainWindow,
					    const sf::Font& textFont,
					    const sf::Font& textHeavyFont,
					    const sf::Font& counterFont);
			void processTimeStep(float dt);
			void handleKeyPressed(sf::Event::KeyEvent key);
			void handleKeyReleased(sf::Event::KeyEvent key);
			void draw();
			virtual ~ClassicGame();
		};

	}
}
#endif
