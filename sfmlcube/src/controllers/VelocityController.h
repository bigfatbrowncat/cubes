/*
 * VelocityController.h
 *
 *  Created on: Dec 3, 2012
 *      Author: imizus
 */

#ifndef VELOCITYCONTROLLER_H_
#define VELOCITYCONTROLLER_H_

namespace sfmlcubes
{
	namespace controllers
	{
		class VelocityController
		{
			static float ROTATION_DURATION_START;
			static float FALLING_DOWN_DURATION_START;
			static float FALLING_DOWN_FAST_DURATION_START;
			static float HORIZONTAL_MOVING_DURATION_START;

			static float ROTATION_DURATION_LIMIT;
			static float FALLING_DOWN_DURATION_LIMIT;
			static float FALLING_DOWN_FAST_DURATION_LIMIT;
			static float HORIZONTAL_MOVING_DURATION_LIMIT;

			static float FALLING_PERIOD;
			static float VELOCITY_MULTIPLICATOR_BY_STEP;
			static float EXPONENT_ARGUMENT_BY_STEP;

			static float FALLING_DOWN_FIRED_DURATION;

			static float BLINKING_DURATION;

		private:
			int step;
			float startToLimit(float start, float limit) const;

		public:
			VelocityController();

			float getRotationLongitude() const;
			float getFallingDownDuration() const;
			float getFallingDownFastDuration() const;
			float getHorizontalMovingDuration() const;
			float getFallingPeriod() const;
			float getVelocityMultiplicator() const;
			float getFallingDownFiredDuration() const;
			float getBlinkingLongitude() const;

			void advanceStep();

			virtual ~VelocityController();
		};
	}
}
#endif
