/*
 * ShapeKinematics.h
 *
 *  Created on: Nov 26, 2012
 *      Author: imizus
 */

#ifndef SHAPEKINEMATICS_H_
#define SHAPEKINEMATICS_H_

#include "transitions/Transition.h"
#include "Shape.h"
#include "ShapeContainer.h"

using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace movingcubes
	{
		class ShapeKinematics
		{
		private:
			ShapeContainer& shapeContainer;

			Transition mHorizontalTransition;
			Transition mVerticalTransition;
			Transition mRotateTransition;
			Transition mBlinkingTransition;
		public:
			ShapeKinematics(ShapeContainer& shapeContainer);

			void advanceStep(double delta);
			bool transitionIsInProgress() const;

			void moveVertical(int cells, Transition::PhaseProcessingFunction function, float longitude);
			void moveHorizontal(int cells, Transition::PhaseProcessingFunction function, float longitude);
			void rotate(int angle, Transition::PhaseProcessingFunction function, float longitude);
			void blink(float longitude, int blinks);

			const Transition& getHorizontalTransition() const { return mHorizontalTransition; }
			const Transition& getVerticalTransition() const { return mVerticalTransition; }
			const Transition& getRotateTransition() const { return mRotateTransition; }
			const Transition& getBlinkingTransition() const { return mBlinkingTransition; }

			virtual ~ShapeKinematics();
		};

	}
}
#endif /* SHAPEKINEMATICS_H_ */
