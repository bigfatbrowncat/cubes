/*
 * ScoreCounter.cpp
 *
 *  Created on: 05.12.2012
 *      Author: IL
 */

#include <math.h>

#include "ScoreCounter.h"

namespace sfmlcubes
{

	ScoreCounter::ScoreCounter(const FallenController& fallenController) :
			score(0),
			fallenController(fallenController)
	{
	}

	void ScoreCounter::shapeHasFallen()
	{
		score += 1;
	}

	void ScoreCounter::linesHasBeenFired()
	{
		int count = fallenController.getLinesJustFired();
		if (count > 0)
		{
			int addScore = pow(2, count) * fallenController.getWidth();
			score += addScore;
		}

	}

	ScoreCounter::~ScoreCounter()
	{
	}

}
