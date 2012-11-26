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
		ShapeKinematics::ShapeKinematics() :
			mBlinkingTransition(1, Transition::ppfConstant, 1)
		{
		}

		void ShapeKinematics::setShape(Shape& shape)
		{
			this->shape = &shape;
		}

		void ShapeKinematics::advanceStep(double delta)
		{
			mRotateTransition.advanceStep(delta);
			shape->rotatingAngle = mRotateTransition.getValue();

			mHorizontalTransition.advanceStep(delta);
			shape->slidingX = mHorizontalTransition.getValue();

			mVerticalTransition.advanceStep(delta);
			shape->slidingY = mVerticalTransition.getValue();

			mBlinkingTransition.advanceStep(delta);
			shape->transparency = mBlinkingTransition.getValue();
		}

		bool ShapeKinematics::transitionIsInProgress() const
		{
			return mRotateTransition.isInProgress() ||
				   mHorizontalTransition.isInProgress() ||
				   mVerticalTransition.isInProgress();
		}

		void ShapeKinematics::moveVertical(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			shape->moveVerticalNoTransition(cells);
			mVerticalTransition = Transition(longitude, function, -cells);
			shape->slidingY = mVerticalTransition.getValue();
		}

		void ShapeKinematics::moveHorizontal(int cells, Transition::PhaseProcessingFunction function, float longitude)
		{
			shape->moveHorizontalNoTransition(cells);
			mHorizontalTransition = Transition(longitude, function, -cells);
			shape->slidingX = mHorizontalTransition.getValue();
		}

		void ShapeKinematics::rotate(int angle, Transition::PhaseProcessingFunction function, float longitude)
		{
			shape->rotateNoTransition(angle);
			mRotateTransition = Transition(longitude, function, -angle);
			shape->rotatingAngle = mRotateTransition.getValue();
		}

		void ShapeKinematics::blink(float longitude, int blinks)
		{
			mBlinkingTransition = Transition(longitude, Transition::ppfAbsSine, blinks);
			shape->transparency = mBlinkingTransition.getValue();
		}

		ShapeKinematics::~ShapeKinematics()
		{
		}

	}
}
