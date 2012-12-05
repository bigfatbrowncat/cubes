#include <string>
#include <sstream>
#include <unistd.h>

#define GLEW_STATIC

#include "CubesMechanic.h"
#include "Logger.h"
#include "WinLinMacApi.h"
#include "ui/TextWithShadow.h"
#include "sfmlcubes.h"

using namespace std;

namespace sfmlcubes
{
	// Global application-level singletones
	static sf::RenderWindow* mainWindow;

	static sf::RenderTexture* mainWindowTexture;
	static sf::Sprite* mainWindowSprite;
	static sf::Shader* mainWindowShader;
	static sf::RenderStates* mainWindowRS;

	static sf::Font* textFont;
	static sf::Font* textHeavyFont;
	static sf::Font* counterFont;

	static sf::Clock clock;

	static sf::Text* pauseText;
	static sf::Text* gameOverText;
	static sf::Text* linesFiredText;
	static sf::Text* linesFiredValueText;
	static sf::Text* scoreText;
	static sf::Text* scoreValueText;
	static sf::Text* speedText;
	static sf::Text* speedValueText;
	//static sf::Text* percentText;
	static sf::Text* nextShapeText;

	static TextWithShadow* pauseTextWithShadow;
	static TextWithShadow* gameOverTextWithShadow;
	static TextWithShadow* linesFiredTextWithShadow;
	static TextWithShadow* linesFiredValueTextWithShadow;
	static TextWithShadow* scoreTextWithShadow;
	static TextWithShadow* scoreValueTextWithShadow;
	static TextWithShadow* speedTextWithShadow;
	static TextWithShadow* speedValueTextWithShadow;
	//static TextWithShadow* percentTextWithShadow;
	static TextWithShadow* nextShapeTextWithShadow;

	static CubesMechanic board(12, 21);

	static float recentMoment = 0;

	static bool rightKeyPressed = false, leftKeyPressed = false, downKeyPressed = false, rotateCWKeyPressed = false;

	// Global application-level functions
	void initMainWindow(const string& title = "Cubes", unsigned int width = 0, unsigned int height = 0, unsigned int antialias = 0)
	{
		int stl = sf::Style::Close;
		sf::VideoMode vm;
		if (width == 0 || height == 0)
		{
			vm = sf::VideoMode::getFullscreenModes()[0];
			stl |= sf::Style::Fullscreen;
		}
		else
		{
			vm = sf::VideoMode(width, height, 32);
		}

		mainWindow->create(vm, title, stl
						  /*| sf::Style::Resize*/,
						  sf::ContextSettings(24, 8, antialias, 1, 6));		// Creating OpenGL 3.2 context

		mainWindow->setFramerateLimit(60);
	}

	void initLayers()
	{
		// Preparing rendering textures
		mainWindowTexture = new sf::RenderTexture();
		mainWindowTexture->create(mainWindow->getSize().x * 2, mainWindow->getSize().y * 2, true);
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

	void initFonts()
	{
		string textFontName(api->locateResource("res/fonts", "OpenSans-Regular.ttf"));
		textFont = new sf::Font();
		textFont->loadFromFile(textFontName);

		string textHeavyFontName(api->locateResource("res/fonts", "OpenSans-Semibold.ttf"));
		textHeavyFont = new sf::Font();
		textHeavyFont->loadFromFile(textHeavyFontName);

		string counterFontName(api->locateResource("res/fonts", "OpenSans-Regular.ttf"));
		counterFont = new sf::Font();
		counterFont->loadFromFile(counterFontName);
	}

	void freeFonts()
	{
		delete textFont;
		delete textHeavyFont;
		delete counterFont;
	}

	void updateStaticText(sf::RenderTarget& win)
	{
		float k = (float)win.getSize().y / 480;

		float panelLeft = 22.0 * win.getSize().x / 28;
		//float panelRight = panelLeft + 90 * k;

		pauseText->setString("Pause");
		pauseText->setCharacterSize(30 * k);
		pauseText->setFont(*textFont);
		pauseText->setPosition(1.0 * win.getSize().x / 2 - pauseText->getGlobalBounds().width / 2,
		                       4.0 * win.getSize().y / 9 - pauseText->getGlobalBounds().height / 2);

		gameOverText->setString("Game over");
		gameOverText->setCharacterSize(30 * k);
		gameOverText->setFont(*textFont);
		gameOverText->setPosition(1.0 * win.getSize().x / 2 - gameOverText->getGlobalBounds().width / 2,
				                  4.0 * win.getSize().y / 9 - gameOverText->getGlobalBounds().height / 2);

		// Speed indicator

		speedText->setString("Speed");
		speedText->setCharacterSize(17 * k);
		speedText->setFont(*textFont);
		speedText->setPosition(panelLeft,
		                       3.8 * win.getSize().y / 8 - speedText->getGlobalBounds().height / 2);

		/*percentText->setString("x");
		percentText->setCharacterSize(17 * k);
		percentText->setFont(*textFont);


		percentText->setPosition(panelRight - percentText->getGlobalBounds().width,
		                         3.8 * win.getSize().y / 8 + 30 * k - percentText->getGlobalBounds().height + 1 * k);*/

		// Lines indicator

		linesFiredText->setString("Lines");
		linesFiredText->setCharacterSize(17 * k);
		linesFiredText->setFont(*textFont);
		linesFiredText->setPosition(panelLeft,
		                            5.1 * win.getSize().y / 8 - linesFiredText->getGlobalBounds().height / 2);

		// Score indicator

		scoreText->setString("Score");
		scoreText->setCharacterSize(17 * k);
		scoreText->setFont(*textHeavyFont);
		scoreText->setPosition(panelLeft,
		                            6.4 * win.getSize().y / 8 - scoreText->getGlobalBounds().height / 2);


		// Next shape

		nextShapeText->setString("Next shape");
		nextShapeText->setCharacterSize(17 * k);
		nextShapeText->setFont(*textFont);
		nextShapeText->setPosition(panelLeft,
		                           1.0 * win.getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2);

		pauseTextWithShadow->setText(*pauseText);
		pauseTextWithShadow->setShadowWidth(3 * k);
		gameOverTextWithShadow->setText(*gameOverText);
		gameOverTextWithShadow->setShadowWidth(3 * k);
		linesFiredTextWithShadow->setText(*linesFiredText);
		linesFiredTextWithShadow->setShadowWidth(3 * k);
		scoreTextWithShadow->setText(*scoreText);
		scoreTextWithShadow->setShadowWidth(3 * k);
		speedTextWithShadow->setText(*speedText);
		speedTextWithShadow->setShadowWidth(3 * k);
		//percentTextWithShadow->setText(*percentText);
		//percentTextWithShadow->setShadowWidth(3 * k);
		nextShapeTextWithShadow->setText(*nextShapeText);
		nextShapeTextWithShadow->setShadowWidth(3 * k);
	}

	void initializeText()
	{
		pauseText = new sf::Text();
		gameOverText = new sf::Text();
		linesFiredText = new sf::Text();
		linesFiredValueText = new sf::Text();
		scoreText = new sf::Text();
		scoreValueText = new sf::Text();
		speedText = new sf::Text();
		speedValueText = new sf::Text();
		//percentText = new sf::Text();
		nextShapeText = new sf::Text();

		pauseTextWithShadow = new TextWithShadow();
		gameOverTextWithShadow = new TextWithShadow();
		linesFiredTextWithShadow = new TextWithShadow();
		linesFiredValueTextWithShadow = new TextWithShadow();
		scoreTextWithShadow = new TextWithShadow();
		scoreValueTextWithShadow = new TextWithShadow();
		speedTextWithShadow = new TextWithShadow();
		speedValueTextWithShadow = new TextWithShadow();
		//percentTextWithShadow = new TextWithShadow();
		nextShapeTextWithShadow = new TextWithShadow();

	}

	void finalizeText()
	{
		delete pauseTextWithShadow;
		delete gameOverTextWithShadow;
		delete linesFiredTextWithShadow;
		delete linesFiredValueTextWithShadow;
		delete scoreTextWithShadow;
		delete scoreValueTextWithShadow;
		delete speedTextWithShadow;
		delete speedValueTextWithShadow;
		//delete percentTextWithShadow;
		delete nextShapeTextWithShadow;

		delete pauseText;
		delete gameOverText;
		delete linesFiredText;
		delete linesFiredValueText;
		delete scoreText;
		delete scoreValueText;
		delete speedText;
		delete speedValueText;
		//delete percentText;
		delete nextShapeText;
	}

	void updateDynamicText(sf::RenderTarget& win)
	{
		float k = (float)win.getSize().y / 480;

		float panelLeft = 22.0 * win.getSize().x / 28;
		float panelRight = panelLeft + 90 * k;

		stringstream ss2;
		ss2.precision(1);
		ss2 << fixed << board.getVelocityIndex();
		speedValueText->setString(ss2.str());
		speedValueText->setColor(sf::Color(192, 192, 128));
		speedValueText->setCharacterSize(30 * k);
		speedValueText->setFont(*counterFont);
		speedValueText->setPosition(panelRight - speedValueText->getGlobalBounds().width - 7 * k,
		                            3.8 * win.getSize().y / 8 + 30 * k - speedValueText->getGlobalBounds().height);

		stringstream ss;
		ss << board.getLinesFired();
		linesFiredValueText->setString(ss.str());
		linesFiredValueText->setColor(sf::Color(192, 128, 128));
		linesFiredValueText->setCharacterSize(30 * k);
		linesFiredValueText->setFont(*counterFont);
		linesFiredValueText->setPosition(panelRight - linesFiredValueText->getGlobalBounds().width - 7 * k,
		                                 5.1 * win.getSize().y / 8 + 13.0 * k);

		stringstream ss3;
		ss3 << board.getScore();
		scoreValueText->setString(ss3.str());
		scoreValueText->setColor(sf::Color(128, 128, 192));
		scoreValueText->setCharacterSize(28 * k);
		scoreValueText->setFont(*textHeavyFont);
		scoreValueText->setPosition(panelRight - scoreValueText->getGlobalBounds().width - 7 * k,
		                                 6.4 * win.getSize().y / 8 + 13.0 * k);

		linesFiredValueTextWithShadow->setText(*linesFiredValueText);
		linesFiredValueTextWithShadow->setShadowWidth(3 * k);
		scoreValueTextWithShadow->setText(*scoreValueText);
		scoreValueTextWithShadow->setShadowWidth(3 * k);
		speedValueTextWithShadow->setText(*speedValueText);
		speedValueTextWithShadow->setShadowWidth(3 * k);
	}

	void drawText(sf::RenderTarget& win, sf::RenderStates rs)
	{
		win.pushGLStates();
		updateDynamicText(win);

		win.draw(*linesFiredTextWithShadow, rs);
		win.draw(*linesFiredValueTextWithShadow, rs);

		win.draw(*scoreTextWithShadow, rs);
		win.draw(*scoreValueTextWithShadow, rs);

		win.draw(*speedTextWithShadow, rs);
		win.draw(*speedValueTextWithShadow, rs);
		//win.draw(*percentTextWithShadow, rs);

		win.draw(*nextShapeTextWithShadow, rs);
		if (board.getState() == cmsGameOver)
		{
			sfmlcubes::mainWindow->setTitle("Cubes (Game Over)");
			win.draw(*gameOverTextWithShadow, rs);
		}
		else if (board.isPaused())
		{
			sfmlcubes::mainWindow->setTitle("Cubes (Paused)");
			win.draw(*pauseTextWithShadow, sf::RenderStates::Default);
		}
		else
		{
			sfmlcubes::mainWindow->setTitle("Cubes");
		}

		win.popGLStates();
	}

	void setPerspective()
	{
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(100.f, (float)mainWindow->getSize().x / mainWindow->getSize().y, 1.f, 1000.f);
	}

	void setView()
	{
		sf::View view(sf::FloatRect(0, 0, mainWindow->getSize().x, mainWindow->getSize().y));
		mainWindow->setView(view);
	}

	void prepareScene()
	{
	    // Set the color and depth clear values
	    glClearDepth(1.f);
	    glClearColor(0.f, 0.f, 0.f, 0.f);

	    // Enable Z-buffer read and write
	    glEnable(GL_DEPTH_TEST);
	    glDepthMask(GL_TRUE);

	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    setPerspective();
	    setView();
	}

	void drawBoard()
	{
		setPerspective();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -300.f);

		//glRotatef(0, 1.f, 0.f, 0.f);
		//glRotatef(0, 0.f, 1.f, 0.f);
		//glRotatef(0, 0.f, 0.f, 1.f);

		// Translating the board center to the center of the screen
		float delta_x = (board.getWidth() - 0.5) / 2;
		float delta_y = (board.getHeight() - 0.5) / 2;
		float cubeSize = 30;

		glScalef(cubeSize, cubeSize, cubeSize);
		glTranslatef(-delta_x, delta_y, 0.f);

		board.glDraw(0, 0);
	}

	void drawNextShape(sf::RenderTexture& win)
	{
		float k = (float)win.getSize().y / 480;

    	glMatrixMode(GL_PROJECTION);
    	Shape dealingShape = board.getShapeDealer().getShape();

    	glLoadIdentity();
    	gluPerspective(35.f, 1, 1, 1000);

		float cubeSize = 40;

    	glViewport(23.0 * win.getSize().x / 28 - nextShapeText->getGlobalBounds().width / 3,
    	           (win.getSize().y - 80 * k) - 1.0 * win.getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2 - 17 * k,

    	           80 * k,
    	           80 * k);

    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
	    glTranslatef(0.f, 0.f, -300.f);	        //gluPerspective()

	    //gluPerspective(100.f, 1, 1.f, 1000.f);

		// Translating the board center to the center of the screen

		glTranslatef(cubeSize * 1.4,
		             cubeSize * 1.4,
		             0.f);
		glRotatef(30, 0.0, -1, -0.5);
		glScalef(cubeSize, cubeSize, cubeSize);

		dealingShape.glDraw(-dealingShape.getRight(), -dealingShape.getTop());
	}

	void drawScene(sf::RenderTexture& win)
	{
		win.pushGLStates();
		win.setActive(true);
//		win.setSmooth(true);
        glViewport(0, 0, win.getSize().x, win.getSize().y);

	    // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

	    // Drawing the cube
	    drawBoard();
	    drawNextShape(win);
		win.popGLStates();

	}

	void handleKeyPressed(sf::Event::KeyEvent key)
	{
    	switch (key.code)
    	{
    	case sf::Keyboard::Escape:
    		mainWindow->close();
    		break;
    	case sf::Keyboard::Right:
    		if (!rightKeyPressed)
    		{
    			rightKeyPressed = true;
    			board.turnOn(cmcMoveRight);
    		}
    		break;
    	case sf::Keyboard::Left:
    		if (!leftKeyPressed)
    		{
    			leftKeyPressed = true;
        		board.turnOn(cmcMoveLeft);
    		}
    		break;
    	case sf::Keyboard::Down:
    		if (!downKeyPressed)
    		{
    			downKeyPressed = true;
        		board.turnOn(cmcMoveDownFast);
    		}
    		break;
    	case sf::Keyboard::Up:
    		if (!rotateCWKeyPressed)
    		{
    			rotateCWKeyPressed = true;
        		board.turnOn(cmcRotateCW);
    		}
    		break;
    	case sf::Keyboard::Space:
    		if (!board.isPaused())
    		{
    			board.turnOn(cmcPause);
    		}
    		else
    		{
    			board.turnOff(cmcPause);
    		}
    		break;
    	default:
    		break;
    	}
	}

	void handleKeyReleased(sf::Event::KeyEvent key)
	{
    	switch (key.code)
    	{
    	case sf::Keyboard::Right:
    		rightKeyPressed = false;
    		board.turnOff(cmcMoveRight);
    		if (leftKeyPressed)
    		{
    			board.turnOn(cmcMoveLeft);
    		}
    		break;
    	case sf::Keyboard::Left:
    		leftKeyPressed = false;
    		board.turnOff(cmcMoveLeft);
    		if (rightKeyPressed)
    		{
    			board.turnOn(cmcMoveRight);
    		}
    		break;
    	case sf::Keyboard::Down:
    		downKeyPressed = false;
    		board.turnOff(cmcMoveDownFast);
    		break;
    	case sf::Keyboard::Up:
    		rotateCWKeyPressed = false;
    		board.turnOff(cmcRotateCW);
    		break;
    	default:
    		break;
    	}
	}

	void handleEvents()
	{
        // Process events
        sf::Event Event;
        while (mainWindow->pollEvent(Event))
        {
        	switch (Event.type)
        	{
        	case sf::Event::Closed:
        		mainWindow->close();
        		break;

        	case sf::Event::KeyPressed:
        		handleKeyPressed(Event.key);
            	break;

        	case sf::Event::KeyReleased:
        		handleKeyReleased(Event.key);
        		break;

           	case sf::Event::Resized:
            	break;

           	default:
           		break;
        	}
        }
	}

	void draw()
	{
		if (board.isPaused())
		{
			usleep(1000 * 50);	// Sleep for 50 msec
		}

		// Creating fullscreen texture for postprocessing
		mainWindowTexture->clear(sf::Color(0, 0, 0, 0));
		drawScene(*mainWindowTexture);
		mainWindowTexture->display();

		mainWindow->clear(sf::Color(32, 32, 20));
		mainWindow->draw(*mainWindowSprite, *mainWindowRS);
		drawText(*mainWindow, sf::RenderStates::Default);

		mainWindow->display();
	}

	void updateStatesAndTiming()
	{
		float curTime = clock.getElapsedTime().asSeconds();

		float dt = curTime - recentMoment;
		recentMoment = curTime;

		board.processTimeStep(dt);
	}

	void run()
	{
	    while (mainWindow->isOpen())
	    {
	    	updateStatesAndTiming();
	    	handleEvents();
	    	draw();
	    }
	}

}

// The entry point
int main()
{
	try
	{
		sfmlcubes::Logger::DEFAULT.logInfo("Logging started");

		sfmlcubes::api = new WinLinMacApi();
		sfmlcubes::initializeText();

		sfmlcubes::mainWindow = new sf::RenderWindow();
		// Create the main window
		sfmlcubes::initMainWindow("Cubes", 800, 600);
		sfmlcubes::initLayers();
		sfmlcubes::TextWithShadow::initialize();
		sfmlcubes::movingcubes::Cube::initialize();
		sfmlcubes::initFonts();
		sfmlcubes::prepareScene();
		sfmlcubes::updateStaticText(*sfmlcubes::mainWindow);

		sfmlcubes::run();

		sfmlcubes::movingcubes::Cube::finalize();
		sfmlcubes::TextWithShadow::finalize();
		sfmlcubes::freeFonts();
		delete sfmlcubes::mainWindow;
		sfmlcubes::finalizeText();
		delete sfmlcubes::api;
	}
	catch (int ex)
	{
		stringstream ss;
		ss << "Caught an error: " << ex << "\n";
		sfmlcubes::Logger::DEFAULT.logError(ss.str());
	}

	sfmlcubes::Logger::DEFAULT.logInfo("Logging finished");
	return EXIT_SUCCESS;
}
