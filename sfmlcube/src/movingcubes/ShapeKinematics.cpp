/*
 * ShapeKinematics.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#include "ShapeKinematics.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		ShapeKinematics::ShapeKinematics(ShapeContainer& shapeContainer) :
			shapeContainer(shapeContainer),
			mBlinkingTransition(1, Transition::ppfConstant, 1)
		{
		}

		void ShapeKinematics::advanceStep(double delta)
		{
			Shape shape = shapeContainer.getShape();

			mRotateTransition.advanceStep(delta);
			shape.rotatingAngle = mRotateTransition.getValue();

			mHorizontalTransition.advanceStep(delta);
			shape.slidingX = mHorizontalTransition.getValue();

			mVerticalTransition.advanceStep(delta);
			shape.slidingY = mVerticalTransition.getValue();

			mBlinkingTransition.advanceStep(delta);
			shape.transparency = mBlinkingTransition.getValue();

			shapeContainer.setShape(shape);
		}

		bool ShapeKinematics::transitionIsInProgress() const
		{
			return mRotateTransition.isInProgress() ||
				   mHorizontalTransition.isInProgress() ||
				   mVerticalTransition.isInProgress();
		}

		void ShapeKinematics::moveVertical(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			Shape shape = shapeContainer.getShape();

			shape.moveVerticalNoTransition(cells);
			mVerticalTransition = Transition(longitude, function, -cells);
			shape.slidingY = mVerticalTransition.getValue();

			shapeContainer.setShape(shape);
		}

		void ShapeKinematics::moveHorizontal(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			Shape shape = shapeContainer.getShape();

			shape.moveHorizontalNoTransition(cells);
			mHorizontalTransition = Transition(longitude, function, -cells);
			shape.slidingX = mHorizontalTransition.getValue();

			shapeContainer.setShape(shape);
		}

		void ShapeKinematics::rotate(int angle, Transition::PhaseProcessingFunction function, float longitude)
		{
			Shape shape = shapeContainer.getShape();

			shape.rotateNoTransition(angle);
			mRotateTransition = Transition(longitude, function, -angle);
			shape.rotatingAngle = mRotateTransition.getValue();

			shapeContainer.setShape(shape);
		}

		void ShapeKinematics::blink(float longitude, int blinks)
		{
			Shape shape = shapeContainer.getShape();

			mBlinkingTransition = Transition(longitude, Transition::ppfAbsSine, blinks);
			shape.transparency = mBlinkingTransition.getValue();

			shapeContainer.setShape(shape);
		}

		ShapeKinematics::~ShapeKinematics()
		{
		}

	}
}
