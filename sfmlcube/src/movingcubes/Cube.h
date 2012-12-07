/*
 * Cube.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	namespace movingcubes
	{
		struct Cube
		{
		public:
			// Inner types
			enum ModelType
			{
				mtVoid,		// Empty cube. Doesn't draw itself at all
				mtPlaying,
				mtWall
			};

		public:
			static sf::Shader* cubeShader;

		public:
			// Fields
			ModelType modelType;
			sf::Color color;
			int x, y;

		public:
			// Functions
			Cube(int x, int y, ModelType modelType, sf::Color color);
			Cube();

			bool operator == (const Cube& other);
			bool operator != (const Cube& other);

		};
	}
}
#endif
