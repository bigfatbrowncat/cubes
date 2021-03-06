/*
 * ShapeState.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include <SFML/Graphics/Color.hpp>

#include "ShapeState.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		ShapeState::ShapeState(const Shape& shape) :
			slidingX(shape.getSlidingXParameter().getValue()),
			slidingY(shape.getSlidingYParameter().getValue()),
			rotatingAngle(shape.getRotatingAngleParameter().getValue()),
			transparency(shape.getTransparencyParameter().getValue()),
			ambient(shape.getAmbient()),
			cubes(shape.getCubes())
		{

		}

		ShapeState::ShapeState(const ShapeState& other) :
			slidingX(other.slidingX),
			slidingY(other.slidingY),
			rotatingAngle(other.rotatingAngle),
			transparency(other.transparency),
			ambient(other.ambient),
			cubes(other.cubes)
		{

		}

		ShapeState::ShapeState(const ShapeCubes& cubes) :
			slidingX(0.0),
			slidingY(0.0),
			rotatingAngle(0.0),
			transparency(1.0),
			ambient(sf::Color(128, 128, 128)),
			cubes(cubes)
		{

		}

		ShapeState::~ShapeState()
		{
			// TODO Auto-generated destructor stub
		}
	}

}
