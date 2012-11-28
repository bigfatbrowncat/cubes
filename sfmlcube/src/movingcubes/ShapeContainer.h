/*
 * ShapeOwner.h
 *
 *  Created on: Nov 28, 2012
 *      Author: imizus
 */

#ifndef SHAPEOWNER_H_
#define SHAPEOWNER_H_

#include "Shape.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		/**
		 * This is an interface for an owner of a shape.
		 * It should provide it's contents to anyone who needs it.
		 */
		class ShapeContainer
		{
		public:
			virtual const Shape& getShape() const = 0;
			virtual void setShape(const Shape& shape) = 0;
		};

	}
}
#endif
