/*
 * TimingManager.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef TIMINGMANAGER_H_
#define TIMINGMANAGER_H_

#include <list>

#include "TimedController.h"

using namespace std;

namespace sfmlcubes
{
	class TimingManager
	{
		friend class TimedController;
	private:
		list<TimedController*> controllers;

		void add(TimedController& tc);
		void remove(TimedController& tc);
	public:
		TimingManager();
		void processTimeStep(double dt);

		virtual ~TimingManager();
	};

}
#endif
