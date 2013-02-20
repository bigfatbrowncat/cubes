/*
 * ShapeState.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef SHAPESTATE_H_
#define SHAPESTATE_H_

#include "Shape.h"
#include "ShapeCubes.h"

namespace sfmlcubes
{

	namespace movingcubes
	{
		class ShapeState
		{
		private:
			double slidingX, slidingY, rotatingAngle, transparency;
			sf::Color ambient;
			ShapeCubes cubes;

		public:
			ShapeState(const Shape& shape);
			ShapeState(const ShapeState& other);
			ShapeState(const ShapeCubes& cubes);

			double getSlidingX() const { return slidingX; }
			double getSlidingY() const { return slidingY; }
			double getRotatingAngle() const { return rotatingAngle; }
			double getTransparency() const { return transparency; }
			sf::Color getAmbient() const { return ambient; }
			const ShapeCubes& getCubes() const { return cubes; }

			virtual ~ShapeState();
		};
	}

}
#endif
