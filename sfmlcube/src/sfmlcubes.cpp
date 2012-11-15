#include <string>

#include "CubesField.h"
#include "sfmlcubes.h"

using namespace std;

namespace sfmlcubes
{
	enum DrawingState
	{
		dsStatic, dsMoving
	};
	static float staticStateDuration = 0.8;	// seconds
	static float movingStateDuration = 0.3;
	static float horizontalMovingDuration = 0.3;

	// Global application-level singletones
	static sf::RenderWindow mainWindow;
	static sf::Font mainFont;
	static sf::Clock clock;

	static CubesField board(8, 14);
	static DrawingState state = dsStatic;
	static float momentWhenDrawingStateChanged = 0;

	static bool movingRightIssued = false;
	static bool movingRightInProgress = false;
	static float momentWhenHorizontalMovingStarted = 0;

	// Global application-level functions
	void initMainWindow(const string& title = "Cubes", unsigned int width = 800, unsigned int height = 600, unsigned int antialias = 8)
	{
		mainWindow.create(sf::VideoMode(width, height, 32),
						  title,
						  sf::Style::Close /*| sf::Style::Resize*/,
						  sf::ContextSettings(24, 8, antialias, 3, 2));		// Creating OpenGL 3.2 context

		mainWindow.setFramerateLimit(60);
	}

	void initMainFont(const string& fontFileName = "res/fonts/arian_amu/arnamu.ttf")
	{
		mainFont.loadFromFile(fontFileName);
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

	    setPerspective();
	    setView();
	}


	//float frame = atan(slope * (horizontalPhase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;

	void drawBoard()
	{
		// Translating the board center to the center of the screen
		int delta_x = board.getWidth() / 2;
		int delta_y = board.getHeight() / 2;
		glTranslatef(-delta_x * Cube::cubesize, delta_y * Cube::cubesize, 0.f);

		board.glDraw();
	}

	void drawScene(const sf::RenderTarget& win, float xangle, float yangle, float zangle)
	{
		mainWindow.setActive(true);

        glViewport(0, 0, mainWindow.getSize().x, mainWindow.getSize().y);

	    // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

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
    		movingRightIssued = true;
    		printf("[LOG] Right key down\n");
    		break;
    	case sf::Keyboard::Left:
    		break;
    	case sf::Keyboard::Up:
    		break;
    	case sf::Keyboard::Down:
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
    		movingRightIssued = false;
    		printf("[LOG] Right key up\n");
    		break;
    	case sf::Keyboard::Left:
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
		mainWindow.display();
	}

	void createNewBlock()
	{
		Cube c = sfmlcubes::Cube(sf::Color::Red, true);
		c.slidingX = -0.5;
		c.slidingY = -0.2;
		c.rotatingAngle = 0.3;
		sfmlcubes::board.setCube(0, 0, c);
		sfmlcubes::board.setCube(0, 1, sfmlcubes::Cube(sf::Color::Green, true));
		sfmlcubes::board.setCube(0, 2, sfmlcubes::Cube(sf::Color::Blue, true));
		sfmlcubes::board.setCube(1, 1, sfmlcubes::Cube(sf::Color::White, true));
	}

	void updateStatesAndTiming()
	{
		float curTime = clock.getElapsedTime().asSeconds();
		float timeSinceDrawingStateChanged = curTime - momentWhenDrawingStateChanged;

		if (movingRightIssued && !movingRightInProgress)
		{
			momentWhenHorizontalMovingStarted = curTime;
			/*if (board.tryMoveRight(cstSlidingAnimation))
			{
				movingRightInProgress = true;
			}*/
		}
		else if (movingRightInProgress && (curTime - momentWhenHorizontalMovingStarted > horizontalMovingDuration))
		{
			//board.tryMoveRight(cstTrueSliding);
			movingRightInProgress = false;
		}

		if (state == dsStatic)
		{
			if (timeSinceDrawingStateChanged > staticStateDuration)
			{
				state = dsMoving;
				momentWhenDrawingStateChanged = curTime;
				printf("[LOG] changed to dsMoving\n");
				//board.calculateFalling(cstSlidingAnimation);
			}
		}
		else if (state == dsMoving)
		{
			if (timeSinceDrawingStateChanged > movingStateDuration)
			{
				state = dsStatic;
				momentWhenDrawingStateChanged = curTime;
				printf("[LOG] changed to dsStatic\n");
				/*if (!board.calculateFalling(cstTrueSliding))
				{
					createNewBlock();
				}*/
			}
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
	sfmlcubes::initMainWindow();
	sfmlcubes::Cube::initGlobal();
	sfmlcubes::initMainFont();
	sfmlcubes::prepareScene();

	sfmlcubes::createNewBlock();

	sfmlcubes::board.setCube(4, 7, sfmlcubes::Cube(sf::Color::Blue, false));

	sfmlcubes::run();

	return EXIT_SUCCESS;
}
