
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

void setPerspective(const sf::Window& win)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, (float)win.getSize().x / win.getSize().y, 1.f, 500.f);
}

void drawCube(const sf::Window& win, float xangle, float yangle, float zangle)
{
    // Set the active window before using OpenGL commands
    // It's useless here because the active window is always the same,
    // but don't forget it if you use multiple windows
	win.setActive();

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply some transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -200.f);
    glRotatef(xangle, 1.f, 0.f, 0.f);
    glRotatef(yangle, 0.f, 1.f, 0.f);
    glRotatef(zangle, 0.f, 0.f, 1.f);

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
}

void updateTextPosition(sf::RenderWindow& win, sf::Text& text)
{
	text.setPosition(win.getSize().x / 2 - text.getGlobalBounds().width / 2,
			         win.getSize().y / 2 - text.getGlobalBounds().height / 2);
}

sf::Text createText(sf::RenderWindow& win, const sf::Font& font)
{
    sf::Text text("Hello", font, 30);
    updateTextPosition(win, text);
    return text;
}

void updateView(sf::RenderWindow& win)
{
	sf::View view(sf::FloatRect(0, 0, win.getSize().x, win.getSize().y));
	//view.setCenter(win.getSize().x / 2, win.getSize().y / 2);
    //view.setSize(win.getSize().x, win.getSize().y);
    win.setView(view);
}

int main()
{
    // Create the main window
	unsigned int antialias = 8;


    sf::RenderWindow app(sf::VideoMode(800, 600, 32),
                   "SFML Window",
                   sf::Style::Close | sf::Style::Resize,
                   sf::ContextSettings(24, 8, antialias, 3, 2));

    //sf::RenderWindow rw;

    app.setFramerateLimit(60);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Load a font
    sf::Font mainFont;

    mainFont.loadFromFile("fonts/arian_amu/arnamu.ttf");

    sf::Text text = createText(app, mainFont);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    setPerspective(app);
    updateView(app);

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event Event;
        while (app.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                app.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                app.close();

            // Resize event : adjust viewport
            if (Event.type == sf::Event::Resized)
            {
                glViewport(0, 0, Event.size.width, Event.size.height);
                setPerspective(app);
                updateTextPosition(app, text);
                updateView(app);
            }
        }

        drawCube(app,
                 clock.getElapsedTime().asSeconds() * 50,
                 clock.getElapsedTime().asSeconds() * 30,
                 clock.getElapsedTime().asSeconds() * 90);

        app.pushGLStates();
        app.draw(text, sf::RenderStates::Default);
        app.popGLStates();

        // Finally, display the rendered frame on screen
        app.display();
    }

    return 0;//EXIT_SUCCESS;
}
