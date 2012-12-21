/*
 * ShapeGenerator.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: imizus
 */

#include "../Logger.h"
#include "ShapeGenerator.h"

namespace sfmlcubes
{
	namespace controllers
	{
		sf::Color ShapeGenerator::generateShapeColor()
		{
			int k = 4;

			float r = 0.3 + 0.6 * ((float)rand() / (RAND_MAX / k)) / k;
			float g = 0.3 + 0.6 * ((float)rand() / (RAND_MAX / k)) / k;
			float b = 0.3 + 0.6 * ((float)rand() / (RAND_MAX / k)) / k;

			return sf::Color(255 * r, 255 * g, 255 * b);
		}


		ShapeGenerator::ShapeGenerator()
		{
			srand (time(NULL));
		}

		Shape ShapeGenerator::createTBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 1, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCenter);
			return res;
		}

		Shape ShapeGenerator::createJBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(1, 1, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCenter);
			return res;
		}

		Shape ShapeGenerator::createLBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(-1, 1, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCenter);
			return res;
		}

		Shape ShapeGenerator::createIBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-2, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(1, 0, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCorner);
			return res;
		}

		Shape ShapeGenerator::createZBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-2, -1, Cube::mtPlaying, gen));
			res.addCube(Cube(-1, -1, Cube::mtPlaying, gen));
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCorner);
			return res;
		}

		Shape ShapeGenerator::createSBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, -1, Cube::mtPlaying, gen));
			res.addCube(Cube(1, -1, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCorner);
			return res;
		}

		Shape ShapeGenerator::createOBlock(const sf::Color& gen)
		{
			Shape res;
			res.addCube(Cube(-1, -1, Cube::mtPlaying, gen));
			res.addCube(Cube(0, -1, Cube::mtPlaying, gen));
			res.addCube(Cube(-1, 0, Cube::mtPlaying, gen));
			res.addCube(Cube(0, 0, Cube::mtPlaying, gen));

			res.setRotatingCenter(0, 0, rctCorner);
			return res;
		}

		Shape ShapeGenerator::createNewShape()
		{
			Shape result;
			sf::Color gen = generateShapeColor();

			int r = (float)rand() / RAND_MAX * 8;
			switch (r)
			{
			case 0:
				result = createOBlock(gen);
				break;
			case 1:
				result = createSBlock(gen);
				break;
			case 2:
				result = createLBlock(gen);
				break;
			case 3:
				result = createJBlock(gen);
				break;
			case 4:
				result = createIBlock(gen);
				break;
			case 5:
				result = createTBlock(gen);
				break;
			case 6:
				result = createSBlock(gen);
				break;
			case 7:
				result = createZBlock(gen);
				break;
			default:
				Logger::DEFAULT.logError("Incorrect random value in the shape generator");
				break;
			}

			return result;

			/*Cube c = sfmlcubes::Cube(sf::Color::Red, true);
			c.slidingX = -0.5;
			c.slidingY = -0.2;
			c.rotatingAngle = 0.3;
			field.cubeAt(0, 0) = c;
			field.cubeAt(0, 1) = sfmlcubes::Cube(sf::Color::Green, true);
			field.cubeAt(0, 2) = sfmlcubes::Cube(sf::Color::Blue, true);
			field.cubeAt(1, 1) = sfmlcubes::Cube(sf::Color::White, true);
			*/
		}

		ShapeGenerator::~ShapeGenerator()
		{
		}
	}
}
