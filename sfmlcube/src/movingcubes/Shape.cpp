/*
 * CubesGroup.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#include <SFML/OpenGL.hpp>

#include "ConstantParameter.h"
#include "Shape.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		Shape::Shape(TimingManager& timingManager) :
			ambient(128, 128, 128, 255),
			slidingX(new ConstantParameter(timingManager, 0.0)),
			slidingY(new ConstantParameter(timingManager, 0.0)),
			rotatingAngle(new ConstantParameter(timingManager, 0.0)),
			transparency(new ConstantParameter(timingManager, 1.0))
		{
		}

		Shape::Shape(const Shape& other) :
			cubes(other.cubes),
			ambient(other.ambient),
			slidingX((Parameter*)other.slidingX->clone()),
			slidingY((Parameter*)other.slidingY->clone()),
			rotatingAngle((Parameter*)other.rotatingAngle->clone()),
			transparency((Parameter*)other.transparency->clone())
		{

		}

		void Shape::setSlidingXParameter(const Parameter& newParameter)
		{
			delete slidingX;
			slidingX = (Parameter*)newParameter.clone();
		}
		void Shape::setSlidingYParameter(const Parameter& newParameter)
		{
			delete slidingY;
			slidingY = (Parameter*)newParameter.clone();
		}
		void Shape::setRotatingAngleParameter(const Parameter& newParameter)
		{
			delete rotatingAngle;
			rotatingAngle = (Parameter*)newParameter.clone();
		}
		void Shape::setTransparencyParameter(const Parameter& newParameter)
		{
			delete transparency;
			transparency = (Parameter*)newParameter.clone();
		}

		bool Shape::isAnyParameterChanging()
		{
			return slidingX->isChanging() ||
			       slidingY->isChanging() ||
			       rotatingAngle->isChanging() ||
			       transparency->isChanging();
		}



		Shape::~Shape()
		{
			delete slidingX;
			delete slidingY;
			delete rotatingAngle;
			delete transparency;
		}

	}
}
