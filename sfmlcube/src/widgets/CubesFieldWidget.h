/*
 * CubesFieldWidget.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CUBESFIELDWIDGET_H_
#define CUBESFIELDWIDGET_H_

#include "../controllers/CubesField.h"
#include "AnimatedPopupsWidget.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget
		{
		private:
			const CubesField& cubesField;

			CubePainter cubePainter;
			ShapePainter shapePainter;

		public:
			CubesFieldWidget(const CubesField& cubesField, const sf::Font& font);
			Coordinates fromCubeInShapeCoordsToFieldCoords(const sf::Vector2u& targetSize, const ShapeState& shapeState, const CubeCoordinates& currentCubeCoords, const Coordinates& coordsInTheCubeSpace) const;
			void drawBoard(sf::RenderTarget& target);
			virtual ~CubesFieldWidget();
		};
	}
}
#endif
