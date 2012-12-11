/*
 * ScoreCounter.cpp
 *
 *  Created on: 05.12.2012
 *      Author: IL
 */

#include <math.h>
#include <sstream>

#include "ScoreCounter.h"

namespace sfmlcubes
{
	namespace controllers
	{
		ScoreCounter::ScoreCounter(const FallenController& fallenController) :
				score(0),
				holesBeforeFallen(0),
				holesAfterFallen(0),
				linesComboCollector(0),
				fallenController(fallenController),
				animatedPopupsManager()
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
			int bonus = 0;
			if (newHoles == holesBeforeFallen)
			{
				// 2. If the shape hasn't make a new hole, giving another point
				bonus += 1;
			}
			else if (newHoles < holesBeforeFallen)
			{
				// 3. If the shape closed the hole, give another 3 points
				bonus += 3;
			}

			// Showing the bonus popup
			if (bonus > 0)
			{
				stringstream ss; ss << "+" << bonus;
				animatedPopupsManager.popup(ss.str());
			}
			score += bonus;

			holesAfterFallen = newHoles;
		}

		void ScoreCounter::linesHasBeenFired()
		{
			int count = fallenController.getLinesJustFired();
			if (count > 0)
			{
				linesComboCollector ++;
				// 4. Giving 10 (width) points for a line, 40 for two, 90 for three and 160 for four
				int addScore = count * count * fallenController.getWidth();

				// 6. [Combo] If you cleared some lines during the consequent falling shapes, you
				// have a bonus, proportional to the square of number of the moves
				score += addScore * linesComboCollector * linesComboCollector;

				int newHoles = fallenController.countHoles();
				if (holesAfterFallen > newHoles && holesBeforeFallen == newHoles)
				{
					// 5. If we created a hole with the falling shape and opened it immediately
					// when the lines has been cleared, give a double bonus to the points for lines clearing
					score += addScore;
				}
			}
			else
			{
				linesComboCollector = 0;
			}

		}

		ScoreCounter::~ScoreCounter()
		{
		}
	}
}
