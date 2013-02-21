/*
 * RowWithKinematics.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef FALLENROW_H_
#define FALLENROW_H_

#include "FallenPart.h"
#include "VelocityController.h"
#include "../movingcubes/TimingManager.h"
#include "BackgroundDealer.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class FallenRow : public sf::NonCopyable, public FallenPart
		{
		public:
			enum Type
			{
				tUnknown, tFallingDown, tBurning, tRemaining
			};

		private:
			int left, right, j;
			Type type;

		public:
			FallenRow(TimingManager& timingManager, const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j);
			static FallenRow* fromDealer(TimingManager& timingManager, const VelocityController& velocityController, BackgroundDealer& backgroundDealer, int left, int right, int j);

			bool lineIsFull();

			void setType(Type value) { type = value; }
			Type getType() const { return type; }

			virtual ~FallenRow() {}
		};

	}
}
#endif
