/*
 * Cube.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include "GL/gl.h"
#include "sfmlcubes.h"
#include "Cube.h"
#include "Logger.h"

namespace sfmlcubes
{


	int Cube::cubesize = 30;
	int Cube::PLAYING_CUBE_INDEX = -1;
	int Cube::WALL_CUBE_INDEX = -1;

	sf::Shader Cube::cubeShader;

	void Cube::initGlobal()
	{
		// Loading the cube model
		PLAYING_CUBE_INDEX = objLoader.load("res/cube.obj", "res");
		WALL_CUBE_INDEX = objLoader.load("res/brick-wall.obj", "res");

		// Loading the cube shader
		if (!cubeShader.loadFromFile("res/cube.vert", "res/cube.frag"))
		{
			Logger::DEFAULT.logWarning("Can't load the cube shader. Sorry...");
		}

	}

	void Cube::glDraw(int dx, int dy) const
	{
		int xx = x + dx;
		int yy = y + dy;

		glPushMatrix();
		glTranslatef(xx * Cube::cubesize, -yy * Cube::cubesize, 0.f);			// Translating the cube

		cubeShader.setParameter("color", (float)color.r / 255, (float)color.g / 255, (float)color.b / 255, (float)color.a / 255);
		cubeShader.setParameter("texture", sf::Shader::CurrentTexture);
		cubeShader.setParameter("light0", 200, 300, 200, 1);
		cubeShader.bind();

		// ** Sliding **

		double hdistance = cubesize * slidingX;
		double vdistance = cubesize * slidingY;
		glTranslatef(hdistance, -vdistance, 0.f);

		// ** Rotating **

		// Moving it back from rotating center
		if (rotatingCenterType == crctCornerOfCube)
		{
			glTranslatef(-cubesize / 2, cubesize / 2, 0.f);
		}
		glTranslatef(cubesize * (rotatingCenterX - xx), -cubesize * (rotatingCenterY - yy), 0.f);

		// Applying rotation
		double angle = 90 * rotatingAngle;
		glRotatef(angle, 0.f, 0.f, -1.f);

		// Moving the cube to it's rotating center
		glTranslatef(-cubesize * (rotatingCenterX - xx), cubesize * (rotatingCenterY - yy), 0.f);
		if (rotatingCenterType == crctCornerOfCube)
		{
			glTranslatef(cubesize / 2, -cubesize / 2, 0.f);
		}

		// ** Drawing the cube **

		glRotatef(90, 1.f, 0.f, 0.f);								// Rotating the cube face to viewer
		glScalef(cubesize / 2, cubesize / 2, cubesize / 2);			// Scaling the cube

		// Drawing the cube
		if (modelType == cmtPlaying)
			sfmlcubes::objLoader.draw(Cube::PLAYING_CUBE_INDEX);
		else
			sfmlcubes::objLoader.draw(Cube::WALL_CUBE_INDEX);

		glPopMatrix();
	}


}
