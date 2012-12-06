#include <string>
#include <sstream>
#include <unistd.h>

#include "controllers/CubesField.h"
#include "Logger.h"
#include "WinLinMacApi.h"
#include "widgets/ClassicGameWidget.h"
#include "sfmlcubes.h"

using namespace std;


namespace sfmlcubes
{
	using namespace widgets;
	using namespace controllers;

	// Global application-level singletones
	static sf::RenderWindow* mainWindow;

	static sf::Font* textFont;
	static sf::Font* textHeavyFont;
	static sf::Font* counterFont;

	static sf::Clock clock;

	static float recentMoment = 0;

	static widgets::ClassicGameWidget* classicGameView;
	static ClassicGameController* classicGameController;

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
        		classicGameController->handleKeyPressed(Event.key);
            	break;

        	case sf::Event::KeyReleased:
        		classicGameController->handleKeyReleased(Event.key);
        		break;

           	case sf::Event::Resized:
            	break;

           	default:
           		break;
        	}
        }
	}

	void updateStatesAndTiming()
	{
		float curTime = clock.getElapsedTime().asSeconds();

		float dt = curTime - recentMoment;
		recentMoment = curTime;

		classicGameController->processTimeStep(dt);
	}

	void run()
	{
	    while (mainWindow->isOpen())
	    {
	    	updateStatesAndTiming();
	    	handleEvents();

	    	classicGameView->draw();
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

		sfmlcubes::mainWindow = new sf::RenderWindow();
		// Create the main window
		sfmlcubes::initMainWindow("Cubes", 640, 480);

		sfmlcubes::widgets::TextWithShadow::initialize();
		sfmlcubes::movingcubes::Cube::initialize();
		sfmlcubes::initFonts();
		//sfmlcubes::prepareScene();

		sfmlcubes::classicGameController = new sfmlcubes::controllers::ClassicGameController();

		sfmlcubes::classicGameView = new sfmlcubes::widgets::ClassicGameWidget(*sfmlcubes::mainWindow,
		                                                        *sfmlcubes::classicGameController,
		                                                        *sfmlcubes::textFont,
		                                                        *sfmlcubes::textHeavyFont,
		                                                        *sfmlcubes::counterFont);

		sfmlcubes::run();

		sfmlcubes::movingcubes::Cube::finalize();
		sfmlcubes::widgets::TextWithShadow::finalize();
		sfmlcubes::freeFonts();
		delete sfmlcubes::mainWindow;
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
