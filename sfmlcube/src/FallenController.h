/*
 * FallenController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLENCONTROLLER_H_
#define FALLENCONTROLLER_H_

#include "movingcubes/Shape.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	class FallenController
	{
		Shape fallen;
	public:
		FallenController();

		const Shape& getFallen() const { return fallen; }

		virtual ~FallenController();
	};
}
#endif
