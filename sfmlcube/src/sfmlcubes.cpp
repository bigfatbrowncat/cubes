#include <string>

#include <SFML/Graphics.hpp>

#include "objloader.h"
#include "CubesField.h"

using namespace std;

namespace sfmlcubes
{
	enum DrawingState
	{
		dsStatic, dsMoving
	};
	static float staticStateDuration = 0.3;	// seconds
	static float movingStateDuration = 0.1;

	// Global application-level singletones
	static sf::RenderWindow mainWindow;
	static sf::Font mainFont;
	static sf::Clock clock;
	static objloader objLoader;

	static int CUBE_OBJECT_INDEX = -1;
	static sf::Shader cubeShader;
	static float cubesize = 40;

	static CubesField board(8, 14);
	static DrawingState state = dsStatic;
	static float momentWhenDrawingStateChanged = 0;

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

	void loadCube()
	{
		CUBE_OBJECT_INDEX = objLoader.load("res/cube-subdivided.obj", "res");
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

	void prepareShaders()
	{
		if (!cubeShader.loadFromFile("res/cube.vert", "res/cube.frag"))
		{
			printf("Can't load the shader. Sorry...");
		}

		cubeShader.setParameter("texture", sf::Shader::CurrentTexture);

		cubeShader.setParameter("light0", 200, 300, 200, 1);
		//shad.setParameter("specular", 10);
		//shad.setParameter("shininess", 3);
		//shad.setParameter("ambient", 0.4, 0.4, 0.4, 1);

	}

	void prepareScene()
	{
	    // Set the color and depth clear values
	    glClearDepth(1.f);
	    glClearColor(0.f, 0.f, 0.f, 0.f);

	    // Enable Z-buffer read and write
	    glEnable(GL_DEPTH_TEST);
	    glDepthMask(GL_TRUE);

	    // Enable blending
	    //glEnable(GL_BLEND);
	    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	    prepareShaders();
	    setPerspective();
	    setView();
	}

	void drawCube(int i, int j, const Cube& cube, double animationPhase)
	{
		glPushMatrix();

		cubeShader.setParameter("color", (float)cube.color.r / 255, (float)cube.color.g / 255, (float)cube.color.b / 255, (float)cube.color.a / 255);
		cubeShader.bind();

		// Applying sliding
		double distance = cubesize * animationPhase;
		switch (cube.slidingDirection)
		{
		case csdDown:
			glTranslatef(0.f, -distance, 0.f);
			break;
		case csdUp:
			glTranslatef(0.f, distance, 0.f);
			break;
		case csdLeft:
			glTranslatef(-distance, 0.f, 0.f);
			break;
		case csdRight:
			glTranslatef(distance, 0.f, 0.f);
			break;
		default:
			break;
		}

		glTranslatef(i * cubesize, -j * cubesize, 0.f);			// Translating the cube

		// Moving it back from rotating center
		glTranslatef(cubesize * (cube.rotatingCenterX - i), -cubesize * (cube.rotatingCenterY - j), 0.f);
		if (cube.rotatingCenterType == crctCornerOfCube)
		{
			glTranslatef(-cubesize / 2, cubesize / 2, 0.f);
		}

		// Applying rotation
		double angle = 90 * animationPhase;
		switch (cube.rotatingDirection)
		{
		case crdCW:
			glRotatef(angle, 0.f, 0.f, -1.f);
			break;
		case crdCCW:
			glRotatef(angle, 0.f, 0.f, 1.f);
			break;
		default:
			break;
		}

		// Moving the cube to it's rotating center
		glTranslatef(-cubesize * (cube.rotatingCenterX - i), cubesize * (cube.rotatingCenterY - j), 0.f);
		if (cube.rotatingCenterType == crctCornerOfCube)
		{
			glTranslatef(cubesize / 2, -cubesize / 2, 0.f);
		}

	    glRotatef(90, 1.f, 0.f, 0.f);								// Rotating the cube face to viewer
	    glScalef(cubesize / 2, cubesize / 2, cubesize / 2);			// Scaling the cube
	    objLoader.draw(CUBE_OBJECT_INDEX);
		glPopMatrix();
	}

	void drawBoard()
	{
		int delta_x = board.getWidth() / 2;
		int delta_y = board.getHeight() / 2;
		glTranslatef(-delta_x * cubesize, delta_y * cubesize, 0.f);			// Translating the cube

		for (int i = 0; i < board.getWidth(); i++)
		for (int j = 0; j < board.getHeight(); j++)
		{
			if (!board.getCube(i, j).empty)
			{
				if (state == dsStatic)
				{
					// Drawing the first, unchanged frame
					drawCube(i, j, board.getCube(i, j), 0);
				}
				else
				{
					float animationPhase = (clock.getElapsedTime().asSeconds() - momentWhenDrawingStateChanged) / movingStateDuration;

					float slope = 1.5;
					float frame = atan(slope * (animationPhase - 0.5)*3.14159*2) / (2 * atan(slope * 3.14159)) + 0.5;

					// Drawing the current frame
					drawCube(i, j, board.getCube(i, j), frame);

				}
			}
		}

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


	void handleKeyboardEvents(sf::Event::KeyEvent key)
	{
    	switch (key.code)
    	{
    	case sf::Keyboard::Escape:
    		mainWindow.close();
    		break;
    	case sf::Keyboard::Right:
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
        		handleKeyboardEvents(Event.key);
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
		Cube c = sfmlcubes::Cube(sf::Color::Green, true, sfmlcubes::csdNone, sfmlcubes::crdCW, sfmlcubes::crctCenterOfCube, 0, 1);
		sfmlcubes::board.setCube(0, 0, c);
		sfmlcubes::board.setCube(0, 1, sfmlcubes::Cube(sf::Color::Red, true, sfmlcubes::csdNone, sfmlcubes::crdCW, sfmlcubes::crctCenterOfCube, 0, 1));
		sfmlcubes::board.setCube(0, 2, sfmlcubes::Cube(sf::Color::Red, true, sfmlcubes::csdNone, sfmlcubes::crdCW, sfmlcubes::crctCenterOfCube, 0, 1));
		sfmlcubes::board.setCube(1, 1, sfmlcubes::Cube(sf::Color::Red, true, sfmlcubes::csdNone, sfmlcubes::crdCW, sfmlcubes::crctCenterOfCube, 0, 1));
	}

	void updateStatesAndTiming()
	{
		float curTime = clock.getElapsedTime().asSeconds();
		float timeSinceDrawingStateChanged = curTime - momentWhenDrawingStateChanged;
		//printf("[LOG] since changed %f\n", timeSinceDrawingStateChanged);
		if (state == dsStatic)
		{
			if (timeSinceDrawingStateChanged > staticStateDuration)
			{
				state = dsMoving;
				momentWhenDrawingStateChanged = curTime;
				printf("[LOG] changed to dsMoving\n");
				board.calculateSliding(cstSlidingAnimation);
			}
		}
		else if (state == dsMoving)
		{
			if (timeSinceDrawingStateChanged > movingStateDuration)
			{
				state = dsStatic;
				momentWhenDrawingStateChanged = curTime;
				printf("[LOG] changed to dsStatic\n");
				if (!board.calculateSliding(cstTrueSliding))
				{
					createNewBlock();
				}
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
	sfmlcubes::initMainFont();
	sfmlcubes::loadCube();
	sfmlcubes::prepareScene();

	sfmlcubes::createNewBlock();

	sfmlcubes::board.setCube(4, 7, sfmlcubes::Cube(sf::Color::Blue, false));

	sfmlcubes::run();

	return EXIT_SUCCESS;
}
