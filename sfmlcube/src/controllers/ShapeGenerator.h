/*
 * ShapeGenerator.h
 *
 *  Created on: Nov 29, 2012
 *      Author: imizus
 */

#ifndef SHAPEGENERATOR_H_
#define SHAPEGENERATOR_H_

#include <SFML/Graphics/Color.hpp>

#include "../movingcubes/Shape.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class ShapeGenerator
		{
		private:
			sf::Color generateShapeColor();
		public:
			ShapeGenerator();

			ShapeCubes createTBlock(const sf::Color& gen);
			ShapeCubes createJBlock(const sf::Color& gen);
			ShapeCubes createLBlock(const sf::Color& gen);
			ShapeCubes createIBlock(const sf::Color& gen);
			ShapeCubes createOBlock(const sf::Color& gen);
			ShapeCubes createSBlock(const sf::Color& gen);
			ShapeCubes createZBlock(const sf::Color& gen);
			ShapeCubes createNewShape();

			virtual ~ShapeGenerator();
		};
	}
}
#endif
