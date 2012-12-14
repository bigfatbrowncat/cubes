/*
 * ScoreCounter.h
 *
 *  Created on: 05.12.2012
 *      Author: IL
 */

#ifndef SCORECOUNTER_H_
#define SCORECOUNTER_H_

#include "AnimatedPopupsManager.h"

#include "FallenController.h"

namespace sfmlcubes
{
	namespace controllers
	{
		class ScoreCounter
		{
		private:
			int score;
			int holesBeforeFallen;
			int holesAfterFallen;
			int linesComboCollector;
			const FallenController& fallenController;
			AnimatedPopupsManager animatedPopupsManager;
			Shape lastFallenShape;
		public:
			ScoreCounter(const FallenController& fallenController);

			void beforeShapeFallen(const Shape& shape);
			void afterShapeFallen();
			void linesHasBeenFired();

			int getScore() const { return score; }
			const AnimatedPopupsManager& getAnimatedPopupsManager() const { return animatedPopupsManager; }

			virtual ~ScoreCounter();
		};
	}
}
#endif
