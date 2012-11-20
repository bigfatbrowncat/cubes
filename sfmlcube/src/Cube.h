/*
 * Cube.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <SFML/Graphics.hpp>

#include "CubeRotatingCenterType.h"

namespace sfmlcubes
{

	enum CubeModelType
	{
		cmtPlaying, cmtWall
	};

	struct Cube
	{
	public:
		// Sliding
		float slidingX, slidingY;

		// Rotating animation
		CubeRotatingCenterType rotatingCenterType;
		int rotatingCenterX, rotatingCenterY;
		float rotatingAngle;	// 1 = 90 degrees

		CubeModelType modelType;
	public:
		static int cubesize;
		static int PLAYING_CUBE_INDEX;
		static int WALL_CUBE_INDEX;
		static sf::Shader cubeShader;

		static void initGlobal();

		sf::Color color;
		int x, y;

		// Constructs non-empty cube
		Cube(CubeModelType modelType, int x, int y, sf::Color color):
			 slidingX(0),
			 slidingY(0),

			 rotatingCenterType(crctCenterOfCube),
			 rotatingCenterX(0),
			 rotatingCenterY(0),
			 rotatingAngle(0),

			 modelType(modelType),

			 color(color),
			 x(x), y(y)

		{

		}

		// Constructs empty cube
		Cube():
		     slidingX(0),
		     slidingY(0),

		     rotatingCenterType(crctCenterOfCube),
		     rotatingCenterX(0),
		     rotatingCenterY(0),
		     rotatingAngle(0),

		     modelType(cmtPlaying),

			 color(color),
			 x(x), y(y)
		{

		}

		void glDraw(int dx, int dy) const;

	};

}
#endif
