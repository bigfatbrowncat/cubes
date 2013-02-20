/*
 * PredictedShapeController.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: imizus
 */

#include "ShapeDealer.h"

namespace sfmlcubes
{
	namespace controllers
	{
		ShapeDealer::ShapeDealer()
		{
			predictedShape = predictedShapeGenerator.createNewShape();
		}

		ShapeCubes ShapeDealer::dealNext()
		{
			ShapeCubes res = predictedShape;
			predictedShape = predictedShapeGenerator.createNewShape();
			return res;
		}

		ShapeDealer::~ShapeDealer()
		{
		}
	}
}
