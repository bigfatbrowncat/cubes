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
		ShapeDealer::ShapeDealer() :
			predictedShapeKinematics(*this)
		{
			predictedShape = predictedShapeGenerator.createNewShape();
		}

		Shape ShapeDealer::dealNext()
		{
			Shape res = predictedShape;
			predictedShape = predictedShapeGenerator.createNewShape();
			return res;
		}

		ShapeDealer::~ShapeDealer()
		{
		}
	}
}
