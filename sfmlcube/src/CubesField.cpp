/*
 * CubesField.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <vector>

#include <SFML/Graphics.hpp>

#include "sfmlcubes.h"
#include "CubesField.h"

using namespace std;


namespace sfmlcubes
{
	int Cube::cubesize = 30;
	int Cube::OBJECT_INDEX = -1;
	sf::Shader Cube::cubeShader;

	void Cube::initGlobal()
	{
		// Loading the cube model
		OBJECT_INDEX = objLoader.load("res/cube-subdivided.obj", "res");

		// Loading the cube shader
		if (!cubeShader.loadFromFile("res/cube.vert", "res/cube.frag"))
		{
			printf("Can't load the shader. Sorry...");
		}

		cubeShader.setParameter("texture", sf::Shader::CurrentTexture);
		cubeShader.setParameter("light0", 200, 300, 200, 1);
	}

	void Cube::glDraw(int i, int j)
	{
		glPushMatrix();
		glTranslatef(i * Cube::cubesize, -j * Cube::cubesize, 0.f);			// Translating the cube

		cubeShader.setParameter("color", (float)color.r / 255, (float)color.g / 255, (float)color.b / 255, (float)color.a / 255);
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
		glTranslatef(cubesize * (rotatingCenterX - i), -cubesize * (rotatingCenterY - j), 0.f);

		// Applying rotation
		double angle = 90 * rotatingAngle;
		glRotatef(angle, 0.f, 0.f, -1.f);

		// Moving the cube to it's rotating center
		glTranslatef(-cubesize * (rotatingCenterX - i), cubesize * (rotatingCenterY - j), 0.f);
		if (rotatingCenterType == crctCornerOfCube)
		{
			glTranslatef(cubesize / 2, -cubesize / 2, 0.f);
		}

		// ** Drawing the cube **

	    glRotatef(90, 1.f, 0.f, 0.f);								// Rotating the cube face to viewer
	    glScalef(cubesize / 2, cubesize / 2, cubesize / 2);			// Scaling the cube

	    // Drawing the cube
	    sfmlcubes::objLoader.draw(Cube::OBJECT_INDEX);

	    glPopMatrix();
	}



	CubesField::CubesField(int width, int height): width(width), height(height)
	{
		cubesData = new Cube[width * height];
	}

	CubesField::~CubesField()
	{
		delete [] cubesData;
	}

	Cube& CubesField::cubeAt(int i, int j)
	{
		return cubesData[width * j + i];
	}

	void CubesField::glDraw() const
	{
		// Drawing the cubes
		for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			if (!cubesData[width * j + i].empty)
			{
				cubesData[width * j + i].glDraw(i, j);
			}
		}
	}

}
