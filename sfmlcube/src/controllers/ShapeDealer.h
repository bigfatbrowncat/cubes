/*
 * PredictedShapeController.h
 *
 *  Created on: Nov 29, 2012
 *      Author: imizus
 */

#ifndef PREDICTEDSHAPECONTROLLER_H_
#define PREDICTEDSHAPECONTROLLER_H_

#include "ShapeGenerator.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		class ShapeDealer
		{
			ShapeGenerator predictedShapeGenerator;
			ShapeCubes predictedShape;
		public:
			ShapeDealer();

			ShapeCubes dealNext();

			const ShapeCubes& getShape() const { return predictedShape; }

			virtual ~ShapeDealer();
		};
	}
}
#endif
