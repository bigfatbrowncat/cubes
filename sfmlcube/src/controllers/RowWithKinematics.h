/*
 * RowWithKinematics.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef ROWWITHKINEMATICS_H_
#define ROWWITHKINEMATICS_H_

#include "ShapeWithKinematics.h"
#include "VelocityController.h"
#include "../movingcubes/TimingManager.h"
#include "BackgroundDealer.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class RowWithKinematics : public sf::NonCopyable, public ShapeWithKinematics
		{
		private:
			int left, right, j;

		public:
			RowWithKinematics(TimingManager& timingManager, const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j);
			static RowWithKinematics* fromDealer(TimingManager& timingManager, const VelocityController& velocityController, BackgroundDealer& backgroundDealer, int left, int right, int j);

			bool lineIsFull();

			virtual ~RowWithKinematics() {}
		};

	}
}
#endif
