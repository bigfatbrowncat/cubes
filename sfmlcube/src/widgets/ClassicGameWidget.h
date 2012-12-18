/*
 * ClassicGame.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CLASSICGAME_H_
#define CLASSICGAME_H_

#include <SFML/Graphics.hpp>
#include "../controllers/ClassicGameController.h"
#include "CubesFieldWidget.h"
#include "ShapeDealerWidget.h"

#include "GaussianGlowingTextPainter.h"
#include "AnimatedPopupTextWidget.h"
#include "AnimatedPopupsWidget.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class ClassicGameWidget
		{
		private:
			sf::RenderWindow& mainWindow;
			const ClassicGameController& gameController;
			const sf::Font& textFont;
			const sf::Font& textHeavyFont;
			const sf::Font& counterFont;
			const sf::Font& counterHeavyFont;

			CubesFieldWidget cubesFieldWidget;
			ShapeDealerWidget shapeDealerWidget;
			AnimatedPopupsWidget animatedPopupsWidget;

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

			GaussianGlowingTextPainter* textWithShadowPainter;

			void initLayers();
			void updateStaticText(sf::RenderTarget& win);
			void updateDynamicText(sf::RenderTarget& win);
			void drawText(sf::RenderTarget& win, sf::RenderStates rs);
			void prepareScene();
			Coordinates fromCubeInShapeCoordsToScreenCoords(const Shape& shape, const CubeCoordinates& currentCubeCoords, const Coordinates& coordsInTheCubeSpace) const;
			void drawScene(sf::RenderTexture& win);
		public:
			ClassicGameWidget(sf::RenderWindow& mainWindow,
			                const ClassicGameController& gameController,
			                const sf::Font& textFont,
			                const sf::Font& textHeavyFont,
			                const sf::Font& counterFont,
			                const sf::Font& counterHeavyFont);
			void draw();
			void processTimeStep(float dt) { animatedPopupsWidget.processTimeStep(dt); }
			virtual ~ClassicGameWidget();
		};

	}
}
#endif
