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
#include "../movingcubes/ShapeContainer.h"
#include "../movingcubes/ShapeKinematics.h"

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		class ShapeDealer : ShapeContainer
		{
			ShapeGenerator predictedShapeGenerator;
			Shape predictedShape;
			ShapeKinematics predictedShapeKinematics;
		public:
			ShapeDealer();

			Shape dealNext();

			Shape getShape() const { return predictedShape; }
			void setShape(const Shape& shape) { predictedShape = shape; }

			virtual ~ShapeDealer();
		};
	}
}
#endif
