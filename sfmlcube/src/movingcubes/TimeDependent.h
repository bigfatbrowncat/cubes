/*
 * TimedController.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef TIMEDEPENDENT_H_
#define TIMEDEPENDENT_H_

namespace sfmlcubes
{
	class TimingManager;

	class TimeDependent
	{
		friend class TimingManager;
	private:
		TimingManager& timingManager;
	protected:
		virtual void processTimeStep(double dt) = 0;
	public:
		TimeDependent(TimingManager& timingManager);
		TimingManager& getTimingManager() const { return timingManager; }

		virtual ~TimeDependent();
	};

}
#endif
