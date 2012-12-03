#include <string>
#include <sstream>
#include <unistd.h>

#include "CubesMechanic.h"
#include "Logger.h"
#include "WinLinMacApi.h"
#include "sfmlcubes.h"

using namespace std;

namespace sfmlcubes
{
	// Global application-level singletones
	static sf::RenderWindow* mainWindow;

	static sf::Font* textFont;
	static sf::Font* counterFont;

	static sf::Clock clock;

	static sf::Text* pauseText;
	static sf::Text* gameOverText;

	static sf::Text* linesFiredText;
	static sf::Text* linesFiredValueText;

	static sf::Text* speedText;
	static sf::Text* speedValueText;

	static sf::Text* percentText;

	static sf::Text* nextShapeText;

	static CubesMechanic board(12, 21);

	static float recentMoment = 0;

	static bool rightKeyPressed = false, leftKeyPressed = false, downKeyPressed = false, rotateCWKeyPressed = false;

	// Global application-level functions
	void initMainWindow(const string& title = "Cubes", unsigned int width = 0, unsigned int height = 0, unsigned int antialias = 8)
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
						  sf::ContextSettings(24, 8, antialias, 3, 2));		// Creating OpenGL 3.2 context

		mainWindow->setFramerateLimit(60);
	}

	void initFonts()
	{
		string textFontName(api->locateResource("res/fonts", "OpenSans-Regular.ttf"));
		textFont = new sf::Font();
		textFont->loadFromFile(textFontName);

		string counterFontName(api->locateResource("res/fonts", "OpenSans-Semibold.ttf"));
		counterFont = new sf::Font();
		counterFont->loadFromFile(counterFontName);
	}

	void freeFonts()
	{
		delete textFont;
		delete counterFont;
	}

	void initializeText()
	{
		pauseText = new sf::Text();
		gameOverText = new sf::Text();

		linesFiredText = new sf::Text();
		linesFiredValueText = new sf::Text();

		speedText = new sf::Text();
		speedValueText = new sf::Text();

		percentText = new sf::Text();

		nextShapeText = new sf::Text();
	}

	void finalizeText()
	{
		delete pauseText;
		delete gameOverText;

		delete linesFiredText;
		delete linesFiredValueText;

		delete speedText;
		delete speedValueText;

		delete percentText;

		delete nextShapeText;
	}

	void updateText()
	{
		float k = (float)mainWindow->getSize().y / 480;

		float panelLeft = 22.0 * mainWindow->getSize().x / 28;
		float panelRight = panelLeft + 90 * k;

		pauseText->setString("Pause");
		pauseText->setCharacterSize(30 * k);
		pauseText->setFont(*textFont);
		pauseText->setPosition(1.0 * mainWindow->getSize().x / 2 - pauseText->getGlobalBounds().width / 2,
		                       4.0 * mainWindow->getSize().y / 9 - pauseText->getGlobalBounds().height / 2);

		gameOverText->setString("Game Over");
		gameOverText->setCharacterSize(30 * k);
		gameOverText->setFont(*textFont);
		gameOverText->setPosition(1.0 * mainWindow->getSize().x / 2 - gameOverText->getGlobalBounds().width / 2,
				                  4.0 * mainWindow->getSize().y / 9 - gameOverText->getGlobalBounds().height / 2);

		// Speed indicator

		speedText->setString("Speed");
		speedText->setCharacterSize(17 * k);
		speedText->setFont(*textFont);
		speedText->setPosition(panelLeft,
		                       5.5 * mainWindow->getSize().y / 8 - speedText->getGlobalBounds().height / 2);

		percentText->setString("x");
		percentText->setCharacterSize(17 * k);
		percentText->setFont(*textFont);

		stringstream ss2;
		ss2.precision(1);
		ss2 << fixed << board.getVelocityMultiplicator();
		speedValueText->setString(ss2.str());
		speedValueText->setColor(sf::Color(192, 192, 128));
		speedValueText->setCharacterSize(30 * k);
		speedValueText->setFont(*counterFont);
		speedValueText->setPosition(panelRight - speedValueText->getGlobalBounds().width - 14 * k,
		                            5.5 * mainWindow->getSize().y / 8 + 30 * k - speedValueText->getGlobalBounds().height);

		percentText->setPosition(panelRight - percentText->getGlobalBounds().width,
		                         5.5 * mainWindow->getSize().y / 8 + 30 * k - percentText->getGlobalBounds().height + 1 * k);

		// Lines indicator

		linesFiredText->setString("Lines");
		linesFiredText->setCharacterSize(17 * k);
		linesFiredText->setFont(*textFont);
		linesFiredText->setPosition(panelLeft,
		                            4.0 * mainWindow->getSize().y / 8 - linesFiredText->getGlobalBounds().height / 2);

		stringstream ss;
		ss << board.getLinesFired();
		linesFiredValueText->setString(ss.str());
		linesFiredValueText->setColor(sf::Color(192, 128, 128));
		linesFiredValueText->setCharacterSize(30 * k);
		linesFiredValueText->setFont(*counterFont);
		linesFiredValueText->setPosition(panelRight - linesFiredValueText->getGlobalBounds().width - 14 * k,
		                                 4.0 * mainWindow->getSize().y / 8 + 13.0 * k);

		// Next shape

		nextShapeText->setString("Next shape");
		nextShapeText->setCharacterSize(17 * k);
		nextShapeText->setFont(*textFont);
		nextShapeText->setPosition(panelLeft,
		                           1.0 * mainWindow->getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2);
	}

	void drawText()
	{
		mainWindow->pushGLStates();
		updateText();

		mainWindow->draw(*linesFiredText, sf::RenderStates::Default);
		mainWindow->draw(*linesFiredValueText, sf::RenderStates::Default);

		mainWindow->draw(*speedText, sf::RenderStates::Default);
		mainWindow->draw(*speedValueText, sf::RenderStates::Default);
		mainWindow->draw(*percentText, sf::RenderStates::Default);

		mainWindow->draw(*nextShapeText, sf::RenderStates::Default);
		if (board.getState() == cmsGameOver)
		{
			sfmlcubes::mainWindow->setTitle("Cubes (Game Over)");
			mainWindow->draw(*gameOverText, sf::RenderStates::Default);
		}
		else if (board.isPaused())
		{
			sfmlcubes::mainWindow->setTitle("Cubes (Paused)");
			mainWindow->draw(*pauseText, sf::RenderStates::Default);
		}
		else
		{
			sfmlcubes::mainWindow->setTitle("Cubes");
		}

		mainWindow->popGLStates();
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
		float k = (float)mainWindow->getSize().y / 480;

		glPushMatrix();
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
		glPopMatrix();

	    glPushMatrix();
		{
	    	Shape dealingShape = board.getShapeDealer().getShape();

	    	glMatrixMode(GL_PROJECTION);
	    	glLoadIdentity();
	    	gluPerspective(35.f, 1, 1, 1000);

			float cubeSize = 40;
/*			float delta_x =  +
	                         nextShapeText->getGlobalBounds().width - k * cubeSize * (dealingShape.getRight() + 1);

			float delta_y =   +
			                 nextShapeText->getGlobalBounds().height - k * cubeSize * (dealingShape.getTop() - 0.5);*/

	    	glViewport(23.0 * mainWindow->getSize().x / 28 - nextShapeText->getGlobalBounds().width / 4,
	    	           (mainWindow->getSize().y - 80 * k) - 1.0 * mainWindow->getSize().y / 8 - nextShapeText->getGlobalBounds().height / 2 - 10 * k,

	    			//,
	    	        //   5.0 * mainWindow->getSize().y / 8 + 20 * k,
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
		glPopMatrix();
	}

	void drawScene(const sf::RenderTarget& win)
	{
		mainWindow->setActive(true);

        glViewport(0, 0, mainWindow->getSize().x, mainWindow->getSize().y);

	    // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        //glDisable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

	    // Apply some transformations


	    // Drawing the cube
	    drawBoard();

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
		drawScene(*mainWindow);
		drawText();
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
		sfmlcubes::movingcubes::Cube::initialize();
		sfmlcubes::initFonts();
		sfmlcubes::prepareScene();

		sfmlcubes::run();

		sfmlcubes::movingcubes::Cube::finalize();
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
