/*
 * Cube.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <GL/gl.h>

#include "../sfmlcubes.h"
#include "../Logger.h"
#include "Cube.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		// Initialization of the Cube static fields
		int Cube::PLAYING_CUBE_INDEX = -1;
		int Cube::WALL_CUBE_INDEX = -1;

		sf::Shader Cube::cubeShader;

		// Cube functions

		void Cube::initialize()
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

		Cube::Cube(int x, int y, Cube::ModelType modelType, sf::Color color):
			 modelType(modelType),
			 color(color),
			 x(x), y(y)

		{
		}

		Cube::Cube():
			 modelType(Cube::mtPlaying),
			 color(color),
			 x(x), y(y)
		{
		}


		void Cube::glDraw() const
		{
			if (modelType != Cube::mtVoid)
			{
				// Drawing the cube

				cubeShader.setParameter("color", (float)color.r / 255, (float)color.g / 255, (float)color.b / 255, (float)color.a / 255);
				cubeShader.setParameter("texture", sf::Shader::CurrentTexture);
				cubeShader.setParameter("light0", 200, 300, 200, 1);
				cubeShader.bind();

				glRotatef(90, 1.f, 0.f, 0.f);								// Rotating the cube face to viewer

				// Drawing the cube
				switch (modelType)
				{
				case Cube::mtPlaying:
					sfmlcubes::objLoader.draw(Cube::PLAYING_CUBE_INDEX);
					break;
				case Cube::mtWall:
					sfmlcubes::objLoader.draw(Cube::WALL_CUBE_INDEX);
					break;
				default:
					break;
				}
			}
		}
	}

}
