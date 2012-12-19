/*
 * ClassicGame.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#include <sstream>
#include <iomanip>
#include "../sfmlcubes.h"
#include "../Logger.h"
#include <SFML/Graphics.hpp>
#include "ClassicGameWidget.h"

using namespace std;

namespace sfmlcubes
{
	namespace widgets
	{

		void ClassicGameWidget::initLayers()
		{
			// Preparing rendering textures
			mainWindowTexture = new sf::RenderTexture();
			mainWindowTexture->create(mainWindow.getSize().x * 2, mainWindow.getSize().y * 2, true);
			mainWindowTexture->setSmooth(true);

			// Preparing rendering sprites
			mainWindowSprite = new sf::Sprite(mainWindowTexture->getTexture());
			mainWindowSprite->setScale(0.5, 0.5);

			// Creating the render states

			// Loading the shaders
			mainWindowShader = new sf::Shader();
			if (!mainWindowShader->loadFromFile(api->locateResource("res", "trivial.vert"), api->locateResource("res", "trivial.frag")))
			{
				Logger::DEFAULT.logError("Can't load main shader.");
			}

			// Preparing RenderStates objects

			mainWindowRS = new sf::RenderStates;
			mainWindowRS->blendMode = sf::BlendAlpha;
			mainWindowRS->shader = mainWindowShader;
			mainWindowShader->setParameter("texture", sf::Shader::CurrentTexture);

		}

		void ClassicGameWidget::updateStaticText(sf::RenderTarget& win)
		{
			float k = (float)win.getSize().y / 480;

			float panelLeft = 22.0 * win.getSize().x / 28;
			//float panelRight = panelLeft + 90 * k;

			pauseText->setString("Pause");
			pauseText->setCharacterSize(30 * k);
			pauseText->setFont(textFont);
			pauseText->setPosition(1.0 * win.getSize().x / 2 - pauseText->getGlobalBounds().width / 2,
								   4.0 * win.getSize().y / 9 - pauseText->getGlobalBounds().height / 2);

			gameOverText->setString("Game over");
			gameOverText->setCharacterSize(30 * k);
			gameOverText->setFont(textFont);
			gameOverText->setPosition(1.0 * win.getSize().x / 2 - gameOverText->getGlobalBounds().width / 2,
									  4.0 * win.getSize().y / 9 - gameOverText->getGlobalBounds().height / 2);

			// Speed indicator

			speedText->setString("Speed");
			speedText->setCharacterSize(17 * k);
			speedText->setFont(textFont);
			speedText->setPosition(panelLeft,
								   3.8 * win.getSize().y / 8 - speedText->getGlobalBounds().height / 2);

			// Lines indicator

			linesFiredText->setString("Lines");
			linesFiredText->setCharacterSize(17 * k);
			linesFiredText->setFont(textFont);
			linesFiredText->setPosition(panelLeft,
										5.1 * win.getSize().y / 8 - linesFiredText->getGlobalBounds().height / 2);

			// Score indicator

			scoreText->setString("Score");
			scoreText->setCharacterSize(17 * k);
			scoreText->setFont(textHeavyFont);
			scoreText->setPosition(panelLeft,
										6.4 * win.getSize().y / 8 - scoreText->getGlobalBounds().height / 2);


			// Next shape

			nextShapeText->setString("Next shape");
			nextShapeText->setCharacterSize(17 * k);
			nextShapeText->setFont(textFont);
			nextShapeText->setPosition(panelLeft,
									   1.0 * win.getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2);

			textWithShadowPainter->setShadowWidth(4 * k);
		}

		void ClassicGameWidget::updateDynamicText(sf::RenderTarget& win)
		{
			float k = (float)win.getSize().y / 480;

			float panelLeft = 22.0 * win.getSize().x / 28;
			float panelRight = panelLeft + 90 * k;

			stringstream ss2;
			ss2.precision(1);
			ss2 << gameController.getCubesField().getVelocityIndex();
			speedValueText->setString(ss2.str());
			speedValueText->setColor(sf::Color(192, 192, 128));
			speedValueText->setCharacterSize(30 * k);
			speedValueText->setFont(counterFont);
			speedValueText->setPosition(panelRight - speedValueText->findCharacterPos(-1).x + speedValueText->findCharacterPos(0).x,
										3.8 * win.getSize().y / 8 + 13 * k);

			stringstream ss;
			ss << gameController.getCubesField().getLinesFired();
			linesFiredValueText->setString(ss.str());
			linesFiredValueText->setColor(sf::Color(192, 128, 128));
			linesFiredValueText->setCharacterSize(30 * k);
			linesFiredValueText->setFont(counterFont);
			linesFiredValueText->setPosition(panelRight - linesFiredValueText->findCharacterPos(-1).x + linesFiredValueText->findCharacterPos(0).x,
											 5.1 * win.getSize().y / 8 + 13.0 * k);

			stringstream ss3;
			ss3 << gameController.getCubesField().getScoreCounter().getScore();
			scoreValueText->setString(ss3.str());
			scoreValueText->setColor(sf::Color(128, 128, 192));
			scoreValueText->setCharacterSize(30 * k);
			scoreValueText->setFont(counterHeavyFont);
			scoreValueText->setPosition(panelRight - scoreValueText->findCharacterPos(-1).x + scoreValueText->findCharacterPos(0).x,
			                            6.4 * win.getSize().y / 8 + 13.0 * k);
		}

		void ClassicGameWidget::drawText(sf::RenderTarget& win, sf::RenderStates rs)
		{
			win.pushGLStates();
			updateDynamicText(win);

			sf::Color shadowColor(0, 0, 0);

			textWithShadowPainter->drawText(*linesFiredText, win, shadowColor, rs);
			textWithShadowPainter->drawText(*linesFiredValueText, win, shadowColor, rs);

			textWithShadowPainter->drawText(*scoreText, win, shadowColor, rs);
			textWithShadowPainter->drawText(*scoreValueText, win, shadowColor, rs);

			textWithShadowPainter->drawText(*speedText, win, shadowColor, rs);
			textWithShadowPainter->drawText(*speedValueText, win, shadowColor, rs);

			textWithShadowPainter->drawText(*nextShapeText, win, shadowColor, rs);
			if (gameController.getCubesField().getState() == cmsGameOver)
			{
				mainWindow.setTitle("Cubes (Game Over)");
				textWithShadowPainter->drawText(*gameOverText, win, shadowColor, rs);
			}
			else if (gameController.getCubesField().isPaused())
			{
				mainWindow.setTitle("Cubes (Paused)");
				textWithShadowPainter->drawText(*pauseText, win, shadowColor, rs);
			}
			else
			{
				mainWindow.setTitle("Cubes");
			}

			//animatedPopupsPainter.paint(gameController.getCubesField().getScoreCounter().getAnimatedPopupsManager(), win, rs);
		    // Drawing the animated text popups
		    animatedPopupsWidget.draw(*textWithShadowPainter, win, sf::RenderStates::Default);

			win.popGLStates();
		}

		void ClassicGameWidget::prepareScene()
		{
		    // Set the color and depth clear values
		    glClearDepth(1.f);
		    glClearColor(0.f, 0.f, 0.f, 0.f);

		    // Enable Z-buffer read and write
		    glEnable(GL_DEPTH_TEST);
		    glDepthMask(GL_TRUE);

		    glEnable(GL_BLEND);
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//sf::View view(sf::FloatRect(0, 0, mainWindow.getSize().x, mainWindow.getSize().y));
			//mainWindow.setView(view);
		}

		void ClassicGameWidget::drawScene(sf::RenderTexture& win)
		{
			float k = (float)win.getSize().y / 480;

			win.pushGLStates();
			win.setActive(true);
	        glViewport(0, 0, win.getSize().x, win.getSize().y);

		    // Clear color and depth buffer
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	        glEnable(GL_DEPTH_TEST);

		    // Drawing the board
		    cubesFieldWidget.drawBoard(win);

		    // Drawing the "next shape" view
	        shapeDealerWidget.setViewport(23.0 * win.getSize().x / 28 - nextShapeText->getGlobalBounds().width / 3,
	    	                              (win.getSize().y - 80 * k) - 1.0 * win.getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2 - 17 * k,
	    	                              80 * k,
	    	                              80 * k);
		    shapeDealerWidget.drawNextShape(win);
			win.popGLStates();

		}

		ClassicGameWidget::ClassicGameWidget(sf::RenderWindow& mainWindow,
		                                 const ClassicGameController& gameController,
		                                 const sf::Font& textFont,
		                                 const sf::Font& textHeavyFont,
		                                 const sf::Font& counterFont,
		                                 const sf::Font& counterHeavyFont) :
		        mainWindow(mainWindow),
		        gameController(gameController),
				textFont(textFont),
				textHeavyFont(textHeavyFont),
				counterFont(counterFont),
				counterHeavyFont(counterHeavyFont),
				cubesFieldWidget(gameController.getCubesField(), textFont),
				shapeDealerWidget(gameController.getCubesField().getShapeDealer()),
				animatedPopupsWidget(gameController.getCubesField().getScoreCounter().getAnimatedPopupsManager(), counterFont, cubesFieldWidget)

		{
			pauseText = new sf::Text();
			gameOverText = new sf::Text();
			linesFiredText = new sf::Text();
			linesFiredValueText = new sf::Text();
			scoreText = new sf::Text();
			scoreValueText = new sf::Text();
			speedText = new sf::Text();
			speedValueText = new sf::Text();
			nextShapeText = new sf::Text();

			textWithShadowPainter = new GaussianGlowingTextPainter();

			initLayers();
			updateStaticText(mainWindow);
			prepareScene();
		}

		void ClassicGameWidget::draw()
		{
			// Creating fullscreen texture for postprocessing
			mainWindowTexture->clear(sf::Color(0, 0, 0, 0));
			drawScene(*mainWindowTexture);
			mainWindowTexture->display();

			mainWindow.clear(sf::Color(32, 32, 20));
			mainWindow.draw(*mainWindowSprite, *mainWindowRS);
			drawText(mainWindow, sf::RenderStates::Default);

			/*
			for (int i = 0; i < gameController.getCubesField().getWidth(); i++)
			for (int j = 0; j < gameController.getCubesField().getHeight(); j++)
			{
				sf::CircleShape cs(1.f, 10);

				CubeCoordinates shapeCenter(i, j);
				Coordinates zero(0, 0, 0);
				Coordinates pos = cubesFieldWidget.fromCubeInShapeCoordsToFieldCoords(mainWindow, gameController.getCubesField().getWallsController().getShape(), shapeCenter, zero);

				cs.setPosition(pos.getX(), pos.getY());
				cs.setFillColor(sf::Color::Red);

				mainWindow.draw(cs, sf::RenderStates::Default);
			}
			 */

			mainWindow.display();
		}

		ClassicGameWidget::~ClassicGameWidget()
		{
			delete textWithShadowPainter;

			delete pauseText;
			delete gameOverText;
			delete linesFiredText;
			delete linesFiredValueText;
			delete scoreText;
			delete scoreValueText;
			delete speedText;
			delete speedValueText;
			delete nextShapeText;
		}

	}
}
