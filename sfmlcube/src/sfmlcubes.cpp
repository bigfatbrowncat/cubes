#include <string>
#include <sstream>

#include "CubesField.h"
#include "CubesMechanic.h"
#include "sfmlcubes.h"

using namespace std;

namespace sfmlcubes
{
	static float fallingPeriod = 1.0;	// seconds

	// Global application-level singletones
	static sf::RenderWindow mainWindow;
	static sf::Font mainFont;
	static sf::Clock clock;

	static sf::Text gameOverText;
	static sf::Text linesFiredText;
	static sf::Text linesFiredValueText;
	static bool showGameOverText = false;

	static CubesMechanic board(12, 21);
	static float momentWhenFallIssued = 0;

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

		mainWindow.create(vm, title, stl
						  /*| sf::Style::Resize*/,
						  sf::ContextSettings(24, 8, antialias, 3, 2));		// Creating OpenGL 3.2 context

		mainWindow.setFramerateLimit(60);
	}

	void initMainFont(const string& fontFileName = "res/fonts/arian_amu/arnamu.ttf")
	{
		mainFont.loadFromFile(fontFileName);
	}

	void updateText()
	{
		float k = (float)mainWindow.getSize().x / 640;

		gameOverText.setString("Game Over");
		gameOverText.setCharacterSize(30 * k);
		gameOverText.setFont(mainFont);
		gameOverText.setPosition(1.0 * mainWindow.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
				                 4.0 * mainWindow.getSize().y / 9 - gameOverText.getGlobalBounds().height / 2);

		linesFiredText.setString("Lines fired");
		linesFiredText.setCharacterSize(15 * k);
		linesFiredText.setFont(mainFont);
		linesFiredText.setPosition(23.0 * mainWindow.getSize().x / 28 - linesFiredText.getGlobalBounds().width / 2,
				                   1.0 * mainWindow.getSize().y / 8 - linesFiredText.getGlobalBounds().height / 2);

		stringstream ss;
		ss << board.getLinesFired();
		linesFiredValueText.setString(ss.str());
		linesFiredValueText.setColor(sf::Color(192, 128, 128));
		linesFiredValueText.setCharacterSize(30 * k);
		linesFiredValueText.setFont(mainFont);
		linesFiredValueText.setPosition(24.0 * mainWindow.getSize().x / 28 - linesFiredValueText.getGlobalBounds().width / 2,
				                   1.0 * mainWindow.getSize().y / 8 + linesFiredText.getGlobalBounds().height + 2.0 * k);


	}

	void drawText()
	{
		mainWindow.pushGLStates();
		updateText();
		mainWindow.draw(linesFiredText, sf::RenderStates::Default);
		mainWindow.draw(linesFiredValueText, sf::RenderStates::Default);
		if (showGameOverText)
		{
			mainWindow.draw(gameOverText, sf::RenderStates::Default);
		}
		mainWindow.popGLStates();
	}

	void setPerspective()
	{
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(100.f, (float)mainWindow.getSize().x / mainWindow.getSize().y, 1.f, 1000.f);
	}

	void setView()
	{
		sf::View view(sf::FloatRect(0, 0, mainWindow.getSize().x, mainWindow.getSize().y));
		mainWindow.setView(view);
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


	//float frame = atan(slope * (horizontalPhase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;

	void drawBoard()
	{
		// Translating the board center to the center of the screen
		float delta_x = board.getField().getWidth() / 2;
		float delta_y = (board.getField().getHeight() + 0.5) / 2;
		glTranslatef(-delta_x * Cube::cubesize, delta_y * Cube::cubesize, 0.f);

		//board.getFieldBackground().glDraw(-1, -1);
		board.getField().glDraw(0, 0);
	}

	void drawScene(const sf::RenderTarget& win, float xangle, float yangle, float zangle)
	{
		mainWindow.setActive(true);

        glViewport(0, 0, mainWindow.getSize().x, mainWindow.getSize().y);

	    // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        //glDisable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

	    // Apply some transformations
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
	    glTranslatef(0.f, 0.f, -300.f);
	    glRotatef(xangle, 1.f, 0.f, 0.f);
	    glRotatef(yangle, 0.f, 1.f, 0.f);
	    glRotatef(zangle, 0.f, 0.f, 1.f);

	    // Drawing the cube
	    drawBoard();

	}


	void handleKeyPressed(sf::Event::KeyEvent key)
	{
    	switch (key.code)
    	{
    	case sf::Keyboard::Escape:
    		mainWindow.close();
    		break;
    	case sf::Keyboard::Right:
    		if (!rightKeyPressed)
    		{
    			rightKeyPressed = true;
    			//board.issueOrder(cmoMoveRight);
    		}
    		break;
    	case sf::Keyboard::Left:
    		if (!leftKeyPressed)
    		{
    			leftKeyPressed = true;
        		//board.issueOrder(cmoMoveLeft);
    		}
    		break;
    	case sf::Keyboard::Down:
    		if (!downKeyPressed)
    		{
    			downKeyPressed = true;
        		//board.issueOrder(cmoMoveDown);
    		}
    		break;
    	case sf::Keyboard::Up:
    		if (!rotateCWKeyPressed)
    		{
    			rotateCWKeyPressed = true;
        		//board.issueOrder(cmoRotateCW);
    		}
    		break;
    	case sf::Keyboard::Space:
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
    		break;
    	case sf::Keyboard::Left:
    		leftKeyPressed = false;
    		break;
    	case sf::Keyboard::Down:
    		downKeyPressed = false;
    		break;
    	case sf::Keyboard::Up:
    		rotateCWKeyPressed = false;
    		break;
    	default:
    		break;
    	}
	}

	void handleEvents()
	{
        // Process events
        sf::Event Event;
        while (mainWindow.pollEvent(Event))
        {
        	switch (Event.type)
        	{
        	case sf::Event::Closed:
        		mainWindow.close();
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
		drawScene(mainWindow, 0, 0, 0);
		drawText();
		mainWindow.display();
	}

	void updateStatesAndTiming()
	{
		float curTime = clock.getElapsedTime().asSeconds();
		float timeSinceFallIssued = curTime - momentWhenFallIssued;

		float dt = curTime - recentMoment;
		board.processTimeStep(dt);
		recentMoment = curTime;

		if (timeSinceFallIssued > fallingPeriod)
		{
			board.issueOrder(cmoMoveDown);
			momentWhenFallIssued = curTime;
		}

	}

	void tryCreateNewBlock()
	{
		if (!board.createNewBlock())
		{
			sfmlcubes::mainWindow.setTitle("Cubes � Game Over");
			showGameOverText = true;
		}
	}

/*	void boardOrderIssuedNotifier(CubesMechanicOrder order, CubesMechanicIssueResponse response)
	{
		if ((order == cmoMoveDown || order == cmoMoveDownFast) && (response == cmirFail))
		{
			board.cleanFrees();
			board.issueOrder(cmoFireLines);
		}
		else if (order == cmoFireLines && response == cmirFail)
		{
			tryCreateNewBlock();
		}
	}

	void boardTransitionFinishedNotifier(CubesMechanicOrder order)
	{
		if (order == cmoFireLines)
		{
			tryCreateNewBlock();
		}
	}
*/

	void boardBeforeOrderIssuedNotifier()
	{
		if (leftKeyPressed)
		{
			board.issueOrder(cmoMoveLeft);
		}
		else if (rightKeyPressed)
		{
			board.issueOrder(cmoMoveRight);
		}
		else if (downKeyPressed)
		{
			board.issueOrder(cmoMoveDownFast);
		}
		else if (rotateCWKeyPressed)
		{
			board.issueOrder(cmoRotateCW);
		}
	}

	void run()
	{
	    while (mainWindow.isOpen())
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
	// Create the main window
	sfmlcubes::initMainWindow("Cubes", 800, 600);
	sfmlcubes::Cube::initGlobal();
	sfmlcubes::initMainFont();
	sfmlcubes::prepareScene();

	//sfmlcubes::board.setOrderIssuedNotifier(sfmlcubes::boardOrderIssuedNotifier);
	sfmlcubes::board.setBeforeOrderIssuingNotifier(sfmlcubes::boardBeforeOrderIssuedNotifier);
	//sfmlcubes::board.setTransitionFinishedNotifier(sfmlcubes::boardTransitionFinishedNotifier);

	sfmlcubes::board.createNewBlock();

	sfmlcubes::run();

	return EXIT_SUCCESS;
}
