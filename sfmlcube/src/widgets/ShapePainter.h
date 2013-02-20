/*
 * ShapePainter.h
 *
 *  Created on: Dec 7, 2012
 *      Author: imizus
 */

#ifndef SHAPEPAINTER_H_
#define SHAPEPAINTER_H_

#include "../movingcubes/ShapeState.h"
#include "../movingcubes/Coordinates.h"
#include "../movingcubes/CubeCoordinates.h"
#include "CubePainter.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace widgets
	{
		class ShapePainter
		{
		private:
			CubePainter& cubePainter;
		public:
			ShapePainter(CubePainter& cubePainter);
			Coordinates fromCubeInShapeCoordsToShapeCoords(const ShapeState& shapeState, CubeCoordinates currentCubeCoords, Coordinates coordsInTheCubeSpace) const;
			void paint(const ShapeState& shapeState) const;
			virtual ~ShapePainter();
		};

	}
}
#endif
