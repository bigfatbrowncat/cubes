/*
 * ScoreCounter.h
 *
 *  Created on: 05.12.2012
 *      Author: IL
 */

#ifndef SCORECOUNTER_H_
#define SCORECOUNTER_H_

#include "FallenController.h"

namespace sfmlcubes
{

	class ScoreCounter
	{
	private:
		int score;
		int holesBeforeFallen;
		int holesAfterFallen;
		const FallenController& fallenController;
	public:
		ScoreCounter(const FallenController& fallenController);

		void beforeShapeFallen();
		void afterShapeFallen();
		void linesHasBeenFired();

		int getScore() const { return score; }

		virtual ~ScoreCounter();
	};

}
#endif
