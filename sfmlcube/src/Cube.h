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

	public:
		static int cubesize;
		static int PLAYING_CUBE_INDEX;
		static int WALL_CUBE_INDEX;
		static sf::Shader cubeShader;

		static void initGlobal();

		sf::Color color;
		int x, y;

		CubeModelType modelType;


		// Constructs non-empty cube
		Cube(CubeModelType modelType, int x, int y, sf::Color color):
			 color(color),
			 x(x), y(y),
			 modelType(cmtPlaying),

			 slidingX(0),
			 slidingY(0),

			 rotatingCenterType(crctCenterOfCube),
			 rotatingCenterX(0),
			 rotatingCenterY(0),
			 rotatingAngle(0)
		{

		}

		// Constructs empty cube
		Cube():
			color(color),

			slidingX(0),
			slidingY(0),

			rotatingCenterType(crctCenterOfCube),
			rotatingCenterX(0),
			rotatingCenterY(0),
			rotatingAngle(0)
		{

		}

		void glDraw(int dx, int dy) const;

	};

}
#endif
