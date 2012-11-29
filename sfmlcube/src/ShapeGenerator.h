/*
 * ShapeGenerator.h
 *
 *  Created on: Nov 29, 2012
 *      Author: imizus
 */

#ifndef SHAPEGENERATOR_H_
#define SHAPEGENERATOR_H_

#include <SFML/Graphics/Color.hpp>

#include "movingcubes/Shape.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{

	class ShapeGenerator
	{
	private:
		sf::Color generateShapeColor();
	public:
		ShapeGenerator();

		Shape createTBlock(const sf::Color& gen);
		Shape createJBlock(const sf::Color& gen);
		Shape createLBlock(const sf::Color& gen);
		Shape createIBlock(const sf::Color& gen);
		Shape createOBlock(const sf::Color& gen);
		Shape createSBlock(const sf::Color& gen);
		Shape createZBlock(const sf::Color& gen);
		Shape createNewShape();

		virtual ~ShapeGenerator();
	};

}
#endif
