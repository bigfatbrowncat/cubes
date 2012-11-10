
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

int main()
{
    // Create the main window
	unsigned int antialias = 8;


    sf::Window app(sf::VideoMode(640, 480, 32),
                   "SFML Window",
                   sf::Style::Close | sf::Style::Resize,
                   sf::ContextSettings(24, 8, antialias, 3, 2));

    app.setFramerateLimit(60);

    // Create a clock for measuring the time elapsed
    sf::Clock Clock;



    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    setPerspective(app);

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
            }
        }

        // Set the active window before using OpenGL commands
        // It's useless here because the active window is always the same,
        // but don't forget it if you use multiple windows
        app.setActive();

        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        glRotatef(Clock.getElapsedTime().asSeconds() * 50, 1.f, 0.f, 0.f);
        glRotatef(Clock.getElapsedTime().asSeconds() * 30, 0.f, 1.f, 0.f);
        glRotatef(Clock.getElapsedTime().asSeconds() * 90, 0.f, 0.f, 1.f);

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

        // Finally, display the rendered frame on screen
        app.display();
    }

    return 0;//EXIT_SUCCESS;
}
