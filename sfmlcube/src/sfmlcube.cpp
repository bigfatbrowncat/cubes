
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/Window.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create the main window
    sf::Window App(sf::VideoMode(640, 480, 32), "SFML Window");

    // Create a clock for measuring the time elapsed
    sf::Clock Clock;

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    // Start the game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();

            // Resize event : adjust viewport
            if (Event.type == sf::Event::Resized)
                glViewport(0, 0, Event.size.width, Event.size.height);
        }

        // Set the active window before using OpenGL commands
        // It's useless here because the active window is always the same,
        // but don't forget it if you use multiple windows
        App.setActive();

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
        App.display();
    }

    return 0;//EXIT_SUCCESS;
}
