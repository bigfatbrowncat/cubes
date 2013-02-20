/*
 * CubesGroup.h
 *
 *  Created on: Nov 20, 2012
 *      Author: imizus
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <list>

#include <SFML/System/NonCopyable.hpp>

#include "Cube.h"
#include "Parameter.h"
#include "../Cloneable.h"
#include "ShapeCubes.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Shape : sf::NonCopyable, public Cloneable
		{
		private:
			ShapeCubes cubes;
		public:
			// Sliding
			Parameter* slidingX;
			Parameter* slidingY;

			// Rotating animation

			Parameter* rotatingAngle;	// 1 = 90 degrees

			// Ambient color
			sf::Color ambient;

			Parameter* transparency;

			Shape(TimingManager& timingManager);
			Shape(const Shape& other);

			void processTimeStep(double delta);

			void setSlidingXParameter(const Parameter& newParameter);
			void setSlidingYParameter(const Parameter& newParameter);
			void setRotatingAngleParameter(const Parameter& newParameter);
			void setTransparencyParameter(const Parameter& newParameter);

			bool isAnyParameterChanging();

			Cloneable* clone() const
			{
				return new Shape(*this);
			}

			const ShapeCubes& getCubes() const { return cubes; }
			void setCubes(const ShapeCubes& value) { cubes = value; }

			void clear() { cubes.clear(); }

			virtual ~Shape();
		};
	}
}
#endif
