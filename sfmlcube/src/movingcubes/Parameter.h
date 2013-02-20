/*
 * Parameter.h
 *
 *  Created on: Feb 18, 2013
 *      Author: imizus
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "../Cloneable.h"
#include "TimeDependent.h"
#include "TimingManager.h"

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Parameter : public Cloneable, public TimeDependent
		{
		public:
			Parameter(TimingManager& timingManager) : TimeDependent(timingManager) {}

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
