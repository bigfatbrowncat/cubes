/*
 * VelocityController.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: imizus
 */

#include <math.h>

#include "VelocityController.h"

namespace sfmlcubes
{
	namespace controllers
	{
		// Constants in this class should be balanced carefully
		// to provide comfort controlling at any game speed.

		// These are used for the game start when the speed is sloooow.
		float VelocityController::ROTATION_DURATION_START = 0.2;
		float VelocityController::FALLING_DOWN_DURATION_START = 0.2;
		float VelocityController::FALLING_DOWN_FAST_DURATION_START = 0.05;
		float VelocityController::HORIZONTAL_MOVING_DURATION_START = 0.11;

		// And these are the limits for "infinity" speed.
		float VelocityController::ROTATION_DURATION_LIMIT = 8;
		float VelocityController::FALLING_DOWN_DURATION_LIMIT = 2;
		float VelocityController::FALLING_DOWN_FAST_DURATION_LIMIT = 0.3;
		float VelocityController::HORIZONTAL_MOVING_DURATION_LIMIT = 4;

		// This is the falling speed. It changes linearly
		float VelocityController::FALLING_PERIOD = 1.0;

		// And these are velocity scales
		float VelocityController::VELOCITY_MULTIPLICATOR_BY_STEP = 1.005;		// For linear velocities
		float VelocityController::EXPONENT_ARGUMENT_BY_STEP = 0.0002;			// For exponential velocities

		float VelocityController::FALLING_DOWN_FIRED_DURATION = 0.3;

		float VelocityController::BLINKING_DURATION = 0.6;

		VelocityController::VelocityController() : step(0)
		{

		}

		float VelocityController::startToLimit(float start, float limit) const
		{
			return limit - (limit - start) * exp(-step * EXPONENT_ARGUMENT_BY_STEP);
		}

		float VelocityController::getRotationLongitude() const
		{
			return startToLimit(ROTATION_DURATION_START, ROTATION_DURATION_LIMIT) / pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}
		float VelocityController::getFallingDownDuration() const
		{
			return startToLimit(FALLING_DOWN_DURATION_START, FALLING_DOWN_DURATION_LIMIT) / pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}
		float VelocityController::getFallingDownFastDuration() const
		{
			return startToLimit(FALLING_DOWN_FAST_DURATION_START, FALLING_DOWN_FAST_DURATION_LIMIT) / pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}
		float VelocityController::getHorizontalMovingDuration() const
		{
			return startToLimit(HORIZONTAL_MOVING_DURATION_START, HORIZONTAL_MOVING_DURATION_LIMIT) / pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}
		float VelocityController::getFallingPeriod() const
		{
			return FALLING_PERIOD / pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}

		float VelocityController::getVelocityMultiplicator() const
		{
			return pow(VELOCITY_MULTIPLICATOR_BY_STEP, step);
		}

		float VelocityController::getFallingDownFiredDuration() const
		{
			return FALLING_DOWN_FIRED_DURATION;
		}

		float VelocityController::getBlinkingLongitude() const
		{
			return BLINKING_DURATION;
		}

		void VelocityController::advanceStep()
		{
			step++;
		}


		VelocityController::~VelocityController()
		{

		}
	}
}
