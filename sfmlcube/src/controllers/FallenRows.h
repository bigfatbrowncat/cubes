/*
 * FallenRows.h
 *
 *  Created on: Feb 21, 2013
 *      Author: imizus
 */

#ifndef FALLENROWS_H_
#define FALLENROWS_H_

#include <list>

#include "FallenRow.h"
#include "../movingcubes/ShapeCubes.h"
#include "../movingcubes/ShapeDynamics.h"

using namespace std;

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class FallenRows
		{
		private:
			list<FallenRow*> lines;
			TimingManager& timingManager;

		public:
			FallenRows(TimingManager& timingManager);

			void give(FallenRow* row);

			FallenRow* editableRowAt(int j);
			const FallenRow* getRowAt(int j) const;

			bool anyCollisionsWithRemainingLines(const ShapeCubes& cubes);
			void startFalling();
			void startBlinking();
			bool isBurningBlinkingInProgress();
			bool isFallingInProgress();
			void addAllRemainingToShapeDynamics(ShapeDynamics& shapeDynamics);
			void setFallByForFallingDown(int fallBy);
			ShapeCubes toShapeCubes();
			void toShapes(list<const Shape*>& shapes) const;

			int countBurningLines();
			void removeBurningLines();
			void clear();

			virtual ~FallenRows();
		};
	}
}
#endif
