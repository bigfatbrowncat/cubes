/*
 * ConstantParameter.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef CONSTANTPARAMETER_H_
#define CONSTANTPARAMETER_H_

#include "Parameter.h"

namespace sfmlcubes
{
	namespace movingcubes
	{

		class ConstantParameter : public Parameter
		{
		private:
			double value;

		public:
			// Constructs the constant with some value
			ConstantParameter(TimingManager& timingManager, double value = 0);

			// Advances the time by delta
			//
			// Implementation: Here it does nothing
			virtual void processTimeStep(double delta) {}

			// Returns the current value
			virtual double getValue() const { return value; }

			// This function should tell if the parameter is changing now,
			// or its changes are already ended
			//
			// Implementation: The constant never changes.
			virtual bool isChanging() const { return false; }

			Cloneable* clone() const
			{
				return new ConstantParameter(*this);
			}

			virtual ~ConstantParameter() {}
		};

	}
}
#endif
