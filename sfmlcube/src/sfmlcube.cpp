
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "objloader.h"

void setPerspective(const sf::Window& win)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.f, (float)win.getSize().x / win.getSize().y, 1.f, 1000.f);
}

void prepareShaders(sf::Shader& shad, sf::Texture& dispTex, sf::Texture& dispNormalDeltaTex)
{
	if (!shad.loadFromFile("res/minimal.vert", "res/minimal.frag"))
	{
		printf("Can't load the shader. Sorry...");
	}

	//dispTex.loadFromFile("res/monkey-disp.png", sf::IntRect(0, 0, 1024, 1024));
	//dispTex.bind(sf::Texture::Normalized);

/*	dispNormalDeltaTex.create(dispTex.getSize().x, dispTex.getSize().y);

	sf::Uint8* dndt = new sf::Uint8[dispTex.getSize().x * dispTex.getSize().y * 4];
	for (int i = 0; i < dispNormalDeltaTex.getSize().x; i++)
	for (int j = 0; j < dispNormalDeltaTex.getSize().y; j++)
	{
		sf::Uint8 b = dndt[(dispTex.getSize().y * j + i) * 4 + 0];
		sf::Uint8 g = dndt[(dispTex.getSize().y * j + i) * 4 + 1];
		sf::Uint8 r = dndt[(dispTex.getSize().y * j + i) * 4 + 2];
		sf::Uint8 a = dndt[(dispTex.getSize().y * j + i) * 4 + 3];



		dndt[(dispTex.getSize().y * j + i) * 4 + 0] = b;
		dndt[(dispTex.getSize().y * j + i) * 4 + 1] = g;
		dndt[(dispTex.getSize().y * j + i) * 4 + 2] = r;
		dndt[(dispTex.getSize().y * j + i) * 4 + 3] = a;

	}
	dispNormalDeltaTex.update(dndt);
	delete [] dndt;*/

	shad.setParameter("texture", sf::Shader::CurrentTexture);
	//shad.setParameter("displacement", dispTex);

	shad.setParameter("lightpos", 50, 50, -100, 1);
	/*shad.setParameter("specular", 10);
	shad.setParameter("shininess", 3);
	shad.setParameter("ambient", 0.4, 0.4, 0.4, 1);*/

}

void drawList(int num, const sf::Shader& shad, const sf::Window& win, float xangle, float yangle, float zangle)
{
    // Set the active window before using OpenGL commands
    // It's useless here because the active window is always the same,
    // but don't forget it if you use multiple windows
	win.setActive();
	shad.bind();

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 10.f, -300.f);
    glScalef(60, 60, 60);
    glRotatef(xangle, 1.f, 0.f, 0.f);
    glRotatef(yangle, 0.f, 1.f, 0.f);
    glRotatef(zangle, 0.f, 0.f, 1.f);


    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    /*GLfloat ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuseLight[4] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specularLight[4] = {0.8, 0.8, 0.8, 1.0};
    GLfloat positionLight[4] = {50, 50, 50, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);*/

    glCallList(num);
    /*
    // Draw a cube
    glBegin(GL_QUADS);

        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f( 50.f,  50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);

        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f,  50.f, 50.f);
        glVertex3f( 50.f,  50.f, 50.f);
        glVertex3f( 50.f, -50.f, 50.f);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f(-50.f,  50.f,  50.f);
        glVertex3f(-50.f, -50.f,  50.f);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f,  50.f, -50.f);
        glVertex3f(50.f,  50.f,  50.f);
        glVertex3f(50.f, -50.f,  50.f);

        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-50.f, -50.f,  50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f,  50.f);

        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-50.f, 50.f,  50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f,  50.f);

    glEnd();
    */
    //shad.unbind();
}

void updateTextPosition(sf::RenderWindow& win, sf::Text& text)
{
	text.setPosition(win.getSize().x / 2 - text.getGlobalBounds().width / 2,
			         3 * win.getSize().y / 4 - text.getGlobalBounds().height / 2);
}

sf::Text createText(sf::RenderWindow& win, const sf::Font& font)
{
    sf::Text text("Zis is da monkey", font, 30);
    updateTextPosition(win, text);
    return text;
}

void updateView(sf::RenderWindow& win)
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

    mainWindow.setFramerateLimit(60);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Load a font
    sf::Font mainFont;

    mainFont.loadFromFile("fonts/arian_amu/arnamu.ttf");

    sf::Text text = createText(mainWindow, mainFont);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    objloader ol;
    int num = ol.load("res/monkey.obj", "res");

    sf::Shader shad;
    sf::Texture dispTex;
    sf::Texture dispNormalDeltaTex;
    prepareShaders(shad, dispTex, dispNormalDeltaTex);

    // Setup a perspective projection
    setPerspective(mainWindow);
    updateView(mainWindow);

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
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                mainWindow.close();

            // Resize event : adjust viewport
            if (Event.type == sf::Event::Resized)
            {
                glViewport(0, 0, Event.size.width, Event.size.height);
                setPerspective(mainWindow);
                updateTextPosition(mainWindow, text);
                updateView(mainWindow);
            }
        }

        drawList(num, shad, mainWindow,
                 /*clock.getElapsedTime().asSeconds() * 50*/0,
                 clock.getElapsedTime().asSeconds() * 30,
                 /*clock.getElapsedTime().asSeconds() * 90*/0);

        mainWindow.pushGLStates();
        mainWindow.draw(text, sf::RenderStates::Default);
        mainWindow.popGLStates();

        // Finally, display the rendered frame on screen
        mainWindow.display();
    }

    return 0;//EXIT_SUCCESS;
}
