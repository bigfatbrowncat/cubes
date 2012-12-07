/*
 * CubeWidget.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: imizus
 */

#include <string>

#include <SFML/OpenGL.hpp>

#include "../sfmlcubes.h"
#include "../Logger.h"

#include "CubePainter.h"

using namespace std;

namespace sfmlcubes
{
	namespace widgets
	{

		CubePainter::CubePainter(Usecase usecase)
		{
			string cubeModelFN, wallModelFN, vertShaderFN, fragShaderFN;

			switch (usecase)
			{
			case uField:
				cubeModelFN = api->locateResource("res", "cube.obj");
				wallModelFN = api->locateResource("res", "brick-wall.obj");
				vertShaderFN = api->locateResource("res", "field.vert");
				fragShaderFN = api->locateResource("res", "field.frag");
				break;
			case uPrediction:
				cubeModelFN = api->locateResource("res", "cube.obj");
				wallModelFN = api->locateResource("res", "brick-wall.obj");
				vertShaderFN = api->locateResource("res", "prediction.vert");
				fragShaderFN = api->locateResource("res", "prediction.frag");
				break;
			}

			// Loading the cube model
			Logger::DEFAULT.logInfo("Initializing cube visualizer. Loading objects");
			playingCubeModelIndex = objLoader.load(cubeModelFN);
			wallCubeModelIndex = objLoader.load(wallModelFN);
			if (playingCubeModelIndex == -1 || wallCubeModelIndex == -1)
			{
				Logger::DEFAULT.logWarning("Can't load the cube model. Sorry...");
			}

			Logger::DEFAULT.logInfo("Loading shader");
			cubeShader = new sf::Shader();
			// Loading the cube shader
			if (!cubeShader->loadFromFile(vertShaderFN, fragShaderFN))
			{
				Logger::DEFAULT.logWarning("Can't load the cube shader. Sorry...");
			}
		}

		CubePainter::~CubePainter()
		{
			if (playingCubeModelIndex != -1)
			{
				glDeleteLists(playingCubeModelIndex, 1);
			}
			if (wallCubeModelIndex != -1)
			{
				glDeleteLists(wallCubeModelIndex, 1);
			}
			delete cubeShader;
		}

		void CubePainter::paint(const Cube& cube) const
		{
			if (cube.modelType != Cube::mtVoid)
			{
				// Drawing the cube

				cubeShader->setParameter("diffuse", (float)cube.color.r / 255, (float)cube.color.g / 255, (float)cube.color.b / 255, (float)cube.color.a / 255);
				cubeShader->setParameter("texture", sf::Shader::CurrentTexture);
				cubeShader->setParameter("light0", 200, 300, 200, 1);
				cubeShader->bind();

				glRotatef(90, 1.f, 0.f, 0.f);								// Rotating the cube face to viewer

				// Drawing the cube
				switch (cube.modelType)
				{
				case Cube::mtPlaying:
					sfmlcubes::objLoader.draw(playingCubeModelIndex);
					break;
				case Cube::mtWall:
					sfmlcubes::objLoader.draw(wallCubeModelIndex);
					break;
				default:
					break;
				}
			}
		}

		void CubePainter::setAmbient(sf::Color c)
		{
			cubeShader->setParameter("ambient", (float)c.r / 255, (float)c.g / 255, (float)c.b / 255, (float)c.a / 255);

		}
		void CubePainter::setTransparency(float t)
		{
			cubeShader->setParameter("transparency", t);
		}


	}
}
