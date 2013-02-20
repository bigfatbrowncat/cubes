/*
 * TimingManager.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef TIMINGMANAGER_H_
#define TIMINGMANAGER_H_

#include <list>

#include "TimeDependent.h"

using namespace std;

namespace sfmlcubes
{
	class TimingManager
	{
		friend class TimeDependent;
	private:
		list<TimeDependent*> controllers;

		void add(TimeDependent& tc);
		void remove(TimeDependent& tc);
	public:
		TimingManager() {}
		void processTimeStep(double dt);

		virtual ~TimingManager() {}
	};

}
#endif
