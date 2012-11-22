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
		// Static fields
		static int cubesize;
		static int PLAYING_CUBE_INDEX;
		static int WALL_CUBE_INDEX;
		static sf::Shader cubeShader;

	public:
		// Fields
		CubeModelType modelType;
		sf::Color color;
		int x, y;

	public:
		// Static functions
		static void initGlobal();

	public:
		// Functions
		Cube(CubeModelType modelType, int x, int y, sf::Color color);
		Cube();

		void glDraw() const;

	};

}
#endif
