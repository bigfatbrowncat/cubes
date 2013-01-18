/*
 * ScoreCounter.cpp
 *
 *  Created on: 05.12.2012
 *      Author: IL
 */

#include <math.h>
#include <sstream>

#include "ScoreCounter.h"

#include "AnimatedPopupMessage.h"
#include "AnimatedPopupLine.h"

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
			AnimatedPopupMessage apm(lastFallenShape);

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
				AnimatedPopupLine apl(ss.str(), bonus, AnimatedPopupLine::tScore, AnimatedPopupLine::atCounter);

				apm.addLine(apl);
				animatedPopupsManager.popup(apm);
			}
			score += bonus;

			holesAfterFallen = newHoles;
		}

		void ScoreCounter::linesHasBeenFired()
		{
			AnimatedPopupMessage apm_message(wallsController.getShape());
			AnimatedPopupMessage apm_counter(lastFallenShape);

			int count = fallenController.getLinesJustFired();
			// Showing the lines popup
			if (count > 0)
			{
				stringstream ss; ss << "+" << count;
				apm_counter.addLine(AnimatedPopupLine(ss.str(), count * 2, AnimatedPopupLine::tLines, AnimatedPopupLine::atCounter));
			}

			int bonus = 0;
			if (count > 0)
			{
				linesComboCollector ++;
				// 4. Giving 10 (width) points for a line, 40 for two, 90 for three and 160 for four
				int addScore = count * count * fallenController.getWidth();
				if (count > 1)
				{
					stringstream ss;
					switch (count)
					{
					case 2:
						ss << "Twins cleared";
						break;
					case 3:
						ss << "Three lines together!";
						break;
					case 4:
						ss << "Four at the same time!";
						break;
					}
					apm_message.addLine(AnimatedPopupLine(ss.str(), count * (3 + linesComboCollector), AnimatedPopupLine::tLines, AnimatedPopupLine::atMessage));
				}

				// 6. [Combo] If you cleared some lines during the consequent falling shapes, you
				// have a bonus, proportional to the square of number of the moves
				bonus = addScore * linesComboCollector * linesComboCollector;
				if (linesComboCollector == 1 && count == 1)
				{
					stringstream ss;
					ss << "Line cleared";
					apm_message.addLine(AnimatedPopupLine(ss.str(), count * (3 + linesComboCollector), AnimatedPopupLine::tLines, AnimatedPopupLine::atMessage));
				}
				else if (linesComboCollector > 1)
				{
					stringstream ss;
					ss << linesComboCollector;
					if (rand() % 2 == 0)
					{
						ss << " in a row";
					}
					else
					{
						ss << " sequently";
					}

					apm_message.addLine(AnimatedPopupLine(ss.str(), count * (3 + linesComboCollector), AnimatedPopupLine::tLines, AnimatedPopupLine::atMessage));
				}

				int newHoles = fallenController.countHoles();
				if (holesAfterFallen > newHoles && holesBeforeFallen == newHoles)
				{
					// 5. If we created a hole with the falling shape and opened it immediately
					// when the lines has been cleared, give a double bonus to the points for lines clearing
					bonus += addScore;
					{
						stringstream ss;
						ss << "Cork bonus";
						apm_message.addLine(AnimatedPopupLine(ss.str(), count * (3 + linesComboCollector), AnimatedPopupLine::tLines, AnimatedPopupLine::atMessage));
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
				apm_message.addLine(AnimatedPopupLine(ss.str(), bonus * 2, AnimatedPopupLine::tScore, AnimatedPopupLine::atCounter));
			}
			score += bonus;

			animatedPopupsManager.popup(apm_message);
			animatedPopupsManager.popup(apm_counter);
		}

		ScoreCounter::~ScoreCounter()
		{
		}
	}
}
