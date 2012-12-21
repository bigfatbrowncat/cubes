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
		ScoreCounter::ScoreCounter(const FallenController& fallenController, const WallsController& wallsController) :
				score(0),
				holesBeforeFallen(0),
				holesAfterFallen(0),
				linesComboCollector(0),
				fallenController(fallenController),
				wallsController(wallsController),
				animatedPopupsManager()
		{
		}

		void ScoreCounter::beforeShapeFallen(const Shape& shape)
		{
			lastFallenShape = shape;
			holesBeforeFallen = fallenController.countHoles();
		}

		void ScoreCounter::afterShapeFallen()
		{
			int newHoles = fallenController.countHoles();
			int bonus = 1; // 1. Giving 1 point for each fallen shape
			if (newHoles == holesBeforeFallen)
			{
				// 2. If the shape hasn't made a new hole, giving another point
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
				animatedPopupsManager.popup(ss.str(), bonus, AnimatedPopupText::tScore, AnimatedPopupText::atBonusCounter, lastFallenShape);
			}
			score += bonus;

			holesAfterFallen = newHoles;
		}

		void ScoreCounter::linesHasBeenFired()
		{
			int count = fallenController.getLinesJustFired();
			// Showing the lines popup
			if (count > 0)
			{
				stringstream ss; ss << "+" << count;
				animatedPopupsManager.popup(ss.str(), count * 2, AnimatedPopupText::tLines, AnimatedPopupText::atBonusCounter, fallenController.getShape());
			}

			int bonus = 0;
			if (count > 0)
			{
				stringstream ss;
				linesComboCollector ++;
				// 4. Giving 10 (width) points for a line, 40 for two, 90 for three and 160 for four
				int addScore = count * count * fallenController.getWidth();
				if (count > 1)
				{
					switch (count)
					{
					case 2:
						ss << "Twins cleared";
						break;
					case 3:
						ss << "Three lines together!";
						break;
					case 4:
						ss << "Four at the same time";
						break;
					}
				}

				// 6. [Combo] If you cleared some lines during the consequent falling shapes, you
				// have a bonus, proportional to the square of number of the moves
				bonus = addScore * linesComboCollector * linesComboCollector;
				if (linesComboCollector > 0)
				{
					if (ss.str().length() > 0) ss << "\n";
					ss << linesComboCollector << " in a row!";
					animatedPopupsManager.popup(ss.str(), count * (3 + linesComboCollector), AnimatedPopupText::tLines, AnimatedPopupText::atTextMessage, wallsController.getShape());
				}

				int newHoles = fallenController.countHoles();
				if (holesAfterFallen > newHoles && holesBeforeFallen == newHoles)
				{
					// 5. If we created a hole with the falling shape and opened it immediately
					// when the lines has been cleared, give a double bonus to the points for lines clearing
					bonus += addScore;
					{
						if (ss.str().length() > 0) ss << "\n";
						stringstream ss; ss << "Cork bonus";
						animatedPopupsManager.popup(ss.str(), count * (3 + linesComboCollector), AnimatedPopupText::tLines, AnimatedPopupText::atTextMessage, wallsController.getShape());
					}
				}
			}
			else
			{
				linesComboCollector = 0;
			}

			// Showing the bonus popup
			if (bonus > 0)
			{
				stringstream ss; ss << "+" << bonus;
				animatedPopupsManager.popup(ss.str(), bonus, AnimatedPopupText::tScore, AnimatedPopupText::atBonusCounter, lastFallenShape);
			}
			score += bonus;
		}

		ScoreCounter::~ScoreCounter()
		{
		}
	}
}
