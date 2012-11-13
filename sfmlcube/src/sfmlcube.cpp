
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "objloader.h"

void setPerspective(const sf::RenderTarget& win)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.f, (float)win.getSize().x / win.getSize().y, 1.f, 1000.f);
}

void prepareShaders(sf::Shader& shad)
{
	if (!shad.loadFromFile("res/minimal.vert", "res/minimal.frag"))
	{
		printf("Can't load the shader. Sorry...");
	}

	shad.setParameter("texture", sf::Shader::CurrentTexture);

	shad.setParameter("light0", 200, 300, 300, 1);
	//shad.setParameter("specular", 10);
	//shad.setParameter("shininess", 3);
	//shad.setParameter("ambient", 0.4, 0.4, 0.4, 1);

}

void drawList(int num, const sf::RenderTarget& win, float xangle, float yangle, float zangle, float scale)
{
    // Clear color and depth buffer

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 10.f, -300.f);
    glScalef(scale, scale, scale);
    glRotatef(xangle, 1.f, 0.f, 0.f);
    glRotatef(yangle, 0.f, 1.f, 0.f);
    glRotatef(zangle, 0.f, 0.f, 1.f);

    glCallList(num);

}

void updateTextPosition(sf::RenderTarget& win, sf::Text& text)
{
	text.setPosition(win.getSize().x / 2 - text.getGlobalBounds().width / 2,
			         3 * win.getSize().y / 4 - text.getGlobalBounds().height / 2);
}

sf::Text createText(sf::RenderTarget& win, const sf::Font& font)
{
    sf::Text text("Zis is da monkey", font, 30);
    updateTextPosition(win, text);
    return text;
}

void updateView(sf::RenderTarget& win)
{
	sf::View view(sf::FloatRect(0, 0, win.getSize().x, win.getSize().y));
    win.setView(view);
}

int main()
{
    // Create the main window
	unsigned int antialias = 8;


    sf::RenderWindow mainWindow(sf::VideoMode(800, 600, 32),
                   "Hello, monkey!",
                   sf::Style::Close | sf::Style::Resize,
                   sf::ContextSettings(24, 8, antialias, 3, 2));

    sf::RenderWindow& renderTex = mainWindow;
    //renderTex.create(mainWindow.getSize().x, mainWindow.getSize().y);

    mainWindow.setFramerateLimit(60);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Load a font
    sf::Font mainFont;

    mainFont.loadFromFile("fonts/arian_amu/arnamu.ttf");

    sf::Text text = createText(renderTex, mainFont);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.5f, 0.5f, 0.5f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    objloader ol;
    int num = ol.load("res/monkey.obj", "res");

    sf::Shader shad;
    prepareShaders(shad);

    // Setup a perspective projection
    setPerspective(renderTex);
    updateView(renderTex);

    float clock_current = clock.getElapsedTime().asSeconds();

    float eta_x = 0, angle_x = 0;
    float eta_y = 0, angle_y = 0;

    // Start the game loop
    while (mainWindow.isOpen())
    {
        // Process events
        sf::Event Event;
        while (mainWindow.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
            	mainWindow.close();

            // Escape key : exit
            if (Event.type == sf::Event::KeyPressed)
            {
            	switch (Event.key.code)
            	{
            	case sf::Keyboard::Escape:
            		mainWindow.close();
            		break;
            	case sf::Keyboard::Right:
            		eta_y += 4;
            		break;
            	case sf::Keyboard::Left:
            		eta_y -= 4;
            		break;
            	case sf::Keyboard::Up:
            		eta_x -= 4;
            		break;
            	case sf::Keyboard::Down:
            		eta_x += 4;
            		break;
            	case sf::Keyboard::Space:
            		eta_x = eta_y = 0;
            		break;
            	default:
            		break;
            	}
            }


            // Resize event : adjust viewport
            if (Event.type == sf::Event::Resized)
            {
                glViewport(0, 0, Event.size.width, Event.size.height);
                setPerspective(renderTex);
                updateTextPosition(renderTex, text);
                updateView(renderTex);
            }
        }

        // Math

        float time_delta = clock.getElapsedTime().asSeconds() - clock_current;
        angle_y += eta_y * time_delta;
        angle_x += eta_x * time_delta;
        clock_current = clock.getElapsedTime().asSeconds();

        eta_x -= 0.1 * eta_x * time_delta;
        eta_y -= 0.1 * eta_y * time_delta;

        if (abs(eta_x) < 0.01) eta_x = 0;
        if (abs(eta_y) < 0.01) eta_y = 0;

        // Graph
        renderTex.setActive();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

    	shad.bind();

        drawList(num, renderTex, angle_x, angle_y, 0, 60);

        renderTex.pushGLStates();
        text.setColor(sf::Color(0, 0, 0));
        renderTex.draw(text, sf::RenderStates::Default);
        renderTex.popGLStates();
        // Finally, display the rendered frame on screen
        renderTex.display();
    }

    return 0;//EXIT_SUCCESS;
}
