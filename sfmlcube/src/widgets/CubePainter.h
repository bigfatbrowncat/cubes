/*
 * CubeWidget.h
 *
 *  Created on: Dec 7, 2012
 *      Author: imizus
 */

#ifndef CUBEWIDGET_H_
#define CUBEWIDGET_H_

#include <SFML/Graphics.hpp>

#include "../movingcubes/Cube.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace widgets
	{
		class CubePainter
		{
		public:
			enum Usecase
			{
				uField,
				uPrediction
			};

		private:
			sf::Shader* cubeShader;
			int playingCubeModelIndex, wallCubeModelIndex;
		public:
			CubePainter(Usecase usecase);
			void paint(const Cube& cube) const;

			void setAmbient(sf::Color c);
			void setTransparency(float t);

			virtual ~CubePainter();
		};

	}
}
#endif
