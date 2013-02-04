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
			static float ROTATION_LONGITUDE_START;
			static float FALLING_DOWN_LONGITUDE_START;
			static float FALLING_DOWN_FAST_LONGITUDE_START;
			static float HORIZONTAL_MOVING_LONGITUDE_START;

			static float ROTATION_LONGITUDE_LIMIT;
			static float FALLING_DOWN_LONGITUDE_LIMIT;
			static float FALLING_DOWN_FAST_LONGITUDE_LIMIT;
			static float HORIZONTAL_MOVING_LONGITUDE_LIMIT;

			static float FALLING_PERIOD;
			static float VELOCITY_MULTIPLICATOR_BY_STEP;
			static float EXPONENT_ARGUMENT_BY_STEP;

			static float FALLING_DOWN_FIRED_LONGITUDE;

		private:
			int step;
			float startToLimit(float start, float limit) const;

		public:
			VelocityController();

			float getRotationLongitude() const;
			float getFallingDownLongitude() const;
			float getFallingDownFastLongitude() const;
			float getHorizontalMovingLongitude() const;
			float getFallingPeriod() const;
			float getVelocityMultiplicator() const;
			float getFallingDownFiredLongitude() const;

			void advanceStep();

			virtual ~VelocityController();
		};
	}
}
#endif
