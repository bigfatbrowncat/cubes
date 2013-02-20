/*
 * Parameter.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "../Cloneable.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Parameter : public Cloneable
		{
		public:
			// Advances the time by delta
			virtual void advanceStep(double delta) = 0;

			// Returns the current value
			virtual double getValue() const = 0;

			// This function should tell if the parameter is changing now,
			// or its changes are already ended
			virtual bool isChanging() const = 0;

			virtual ~Parameter() {}
		};
	}
}
#endif
