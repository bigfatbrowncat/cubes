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

			enum RotatingCenterType
			{
				rctCenter, rctCorner
			};

		private:
			// Static fields
			static int PLAYING_CUBE_INDEX;
			static int WALL_CUBE_INDEX;
		public:
			static sf::Shader cubeShader;

		public:
			// Fields
			ModelType modelType;
			sf::Color color;
			int x, y;

		public:
			// Static functions
			static void initialize();

		public:
			// Functions
			Cube(int x, int y, ModelType modelType, sf::Color color);
			Cube();

			void glDraw() const;

			bool operator == (const Cube& other);
			bool operator != (const Cube& other);

		};
	}
}
#endif
