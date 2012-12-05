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
			holesBeforeFallen(0),
			holesAfterFallen(0),
			fallenController(fallenController)
	{
	}

	void ScoreCounter::beforeShapeFallen()
	{
		// 1. Giving 1 point for a fallen shape
		score += 1;
		holesBeforeFallen = fallenController.countHoles();
	}

	void ScoreCounter::afterShapeFallen()
	{
		int newHoles = fallenController.countHoles();
		if (newHoles == holesBeforeFallen)
		{
			// 2. If the shape hasn't make a new hole, giving another point
			score += 1;
		}
		else if (newHoles < holesBeforeFallen)
		{
			// 3. If the shape closed the hole, give another 3 points
			score += 3;
		}
		holesAfterFallen = newHoles;
	}

	void ScoreCounter::linesHasBeenFired()
	{
		int count = fallenController.getLinesJustFired();
		if (count > 0)
		{
			// 4. Giving 10 (width) points for a line, 20 for two, 40 for three and 80 for four
			int addScore = pow(2, count - 1) * fallenController.getWidth();
			score += addScore;

			int newHoles = fallenController.countHoles();
			if (holesAfterFallen > newHoles && holesBeforeFallen == newHoles)
			{
				// 5. If we created a hole with the falling shape and opened it immediately
				// when the lines has been cleared, give a double bonus to the points for lines clearing
				score += addScore;
			}
		}

	}

	ScoreCounter::~ScoreCounter()
	{
	}

}
