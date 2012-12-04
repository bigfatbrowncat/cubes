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
		const FallenController& fallenController;
	public:
		ScoreCounter(const FallenController& fallenController);

		void shapeHasFallen();
		void linesHasBeenFired();

		int getScore() const { return score; }

		virtual ~ScoreCounter();
	};

}
#endif
