/*
 * FallenController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLENCONTROLLER_H_
#define FALLENCONTROLLER_H_

#include "movingcubes/ShapeContainer.h"
#include "movingcubes/Shape.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	class FallenController : public ShapeContainer
	{
		Shape fallen;
	public:
		FallenController();

		const Shape& getShape() const { return fallen; }
		void setShape(const Shape& shape) { fallen = shape; }

		void mergeShape(const Shape& other) { fallen += other; }

		virtual ~FallenController();
	};
}
#endif
