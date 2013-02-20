/*
 * ShapeKinematics.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#include "ShapeKinematics.h"
#include "transitions/TransitionableParameter.h"
#include "transitions/AbsCosinePhaseProcessingFunction.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		ShapeKinematics::ShapeKinematics(Shape& shape) :
			shape(shape)
		{
		}

		void ShapeKinematics::processTimeStep(double delta)
		{
		}

		bool ShapeKinematics::transitionIsInProgress() const
		{
			return shape.isAnyParameterChanging();
		}

		void ShapeKinematics::moveVertical(int cells, const PhaseProcessingFunction& function, float longitude)
		{
			ShapeCubes sc = shape.getCubes();
			sc.moveVerticalNoTransition(cells);
			shape.setCubes(sc);
			shape.setSlidingYParameter(TransitionableParameter(longitude, function, -cells, 0));
		}

		void ShapeKinematics::moveHorizontal(int cells, const PhaseProcessingFunction& function, float longitude)
		{
			ShapeCubes sc = shape.getCubes();
			sc.moveHorizontalNoTransition(cells);
			shape.setCubes(sc);
			shape.setSlidingXParameter(TransitionableParameter(longitude, function, -cells, 0));
		}

		void ShapeKinematics::rotate(int angle, const PhaseProcessingFunction& function, float longitude)
		{
			ShapeCubes sc = shape.getCubes();
			sc.rotateNoTransition(angle);
			shape.setCubes(sc);
			shape.setRotatingAngleParameter(TransitionableParameter(longitude, function, -angle, 0));
		}

		void ShapeKinematics::blink(float longitude, int blinks)
		{
			shape.setTransparencyParameter(TransitionableParameter(longitude, AbsCosinePhaseProcessingFunction(), 0, 1));
		}

		ShapeKinematics::~ShapeKinematics()
		{
		}

	}
}
