/*
 * TimedController.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef TIMEDCONTROLLER_H_
#define TIMEDCONTROLLER_H_

namespace sfmlcubes
{
	class TimingManager;

	class TimedController
	{
		friend class TimingManager;
	private:
		TimingManager& timingManager;
		virtual void processTimeStep(float dt) = 0;
	public:
		TimedController(TimingManager& timingManager);
		~TimedController();
	};

}
#endif
