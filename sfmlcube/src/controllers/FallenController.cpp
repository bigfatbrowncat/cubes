/*
 * FallenController.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */
#include <sstream>

#include "../movingcubes/ShapeDynamics.h"

#include "../Logger.h"
#include "FallenController.h"

using namespace std;
using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	namespace controllers
	{
		float FallenController::FALLING_DOWN_FIRED_LONGITUDE = 0.3;
		float FallenController::BLINKING_LONGITUDE = 0.6;

		FallenController::FallenController(int left, int top, int right, int bottom) :
				state(sPassive),
				left(left), top(top), right(right), bottom(bottom),
				linesFired(0),
				linesJustFired(0),
				fallenKinematics(*this)
		{
		}

		void FallenController::processTimeStep(float dt)
		{
			fallenKinematics.advanceStep(dt);
			for (list<ShapeKinematics*>::iterator iter = fallenNotFiredPartKinematics.begin();
				 iter != fallenNotFiredPartKinematics.end();
				 iter ++)
			{
				(*iter)->advanceStep(dt);
			}

			switch (state)
			{
			case sPassive:
				// Do nothing
				break;
			case sBlinkingFullLines:
				if (!fallenKinematics.getBlinkingTransition().isInProgress())
				{
					removeFiredAwayLines();
					state = sFiringFullLines;
				}
				break;
			case sFiringFullLines:
				if (!anyFiringTransitionsInProgress())
				{
					firingGroupsToFallen();
					state = sPassive;
				}
				break;
			}
		}

		bool FallenController::anyCollisions(const Shape& shape)
		{
			ShapeDynamics sd(shape);

			for (list<Shape*>::const_iterator iter = fallenNotFiredParts.begin();
				 iter != fallenNotFiredParts.end();
				 iter ++)
			{
				sd.addObstacle(**iter);
			}
			sd.addObstacle(fallen);

			return sd.anyCollisions();
		}

		void FallenController::collectLinesToFire()
		{
			linesJustFired = 0;
			bool previousLineWasFired = true;
			int moveBy = 0;
			for (int j = bottom; j >= top; j--)
			{
				// Check if this line is full
				bool thisRowIsFull = true;
				for (int i = left; i <= right; i++)
				{
					if (fallen.cubeAt(i, j).empty()) thisRowIsFull = false;
				}

				if (thisRowIsFull)
				{
					// First of all we close the recent group if it exists
					if (!previousLineWasFired && fallenNotFiredParts.size() > 0)
					{
						firingLineCounts.insert(pair<ShapeKinematics*, int> (fallenNotFiredPartKinematics.back(), moveBy) );
					}

					linesJustFired ++;
					moveBy ++;
					previousLineWasFired = true;
				}
				else
				{
					// This line isn't fired
					if (previousLineWasFired)
					{
						// The last line was fired, so we start a new group

						// and then we create a new one
						Shape* s = new Shape();
						ShapeKinematics* sd = new ShapeKinematics(*s);

						fallenNotFiredParts.push_back(s);
						fallenNotFiredPartKinematics.push_back(sd);
					}

					// Adding the line to the current group
					for (int i = left; i <= right; i++)
					{
						if (!fallen.cubeAt(i, j).empty())
						{
							// Adding the cube to the current firing group
							fallenNotFiredParts.back()->addCube(fallen.cubeAt(i, j).back());
							// Removing the cube from the fallens
							fallen.removeCube(i, j);
						}
					}
					previousLineWasFired = false;
				}
			}

			// close the last group
			if (fallenNotFiredParts.size() > 0)
			{
				if (moveBy > 0)
				{
					firingLineCounts.insert(pair<ShapeKinematics*, int> (fallenNotFiredPartKinematics.back(), moveBy) );
				}
			}

			//linesFired += count;

			if (moveBy > 0)
			{
				// Starting the blinking of the firing lines
				fallenKinematics.blink(BLINKING_LONGITUDE, 3);
				state = sBlinkingFullLines;
			}
			else
			{
				// Nothing to fire

				state = sFiringFullLines;
			}
		}

		void FallenController::removeFiredAwayLines()
		{
			for (map<ShapeKinematics*, int>::iterator iter = firingLineCounts.begin(); iter != firingLineCounts.end(); iter++)
			{
				(*iter).first->moveVertical((*iter).second, Transition::ppfParabolic, FALLING_DOWN_FIRED_LONGITUDE);
			}

			linesFired += linesJustFired;

			{
				stringstream ss;
				ss << "Just cleared: " << linesJustFired << " lines";
				Logger::DEFAULT.logInfo(ss.str());
			}

			// Clearing the fallen part of the board
			fallen.clear();
		}

		bool FallenController::anyFiringTransitionsInProgress()
		{
			for (list<ShapeKinematics*>::iterator iter = fallenNotFiredPartKinematics.begin();
				 iter != fallenNotFiredPartKinematics.end();
				 iter++)
			{
				if ((*iter)->transitionIsInProgress()) return true;
			}
			return false;
		}

		void FallenController::firingGroupsToFallen()
		{
			while (fallenNotFiredParts.size() > 0)
			{
				Shape* cg = fallenNotFiredParts.back();

				fallen += *cg;

				fallenNotFiredParts.remove(cg);
				delete cg;
			}

			while (fallenNotFiredPartKinematics.size() > 0)
			{
				ShapeKinematics* kin = fallenNotFiredPartKinematics.back();
				fallenNotFiredPartKinematics.remove(kin);
				firingLineCounts.erase(kin);
				delete kin;
			}
		}

		int FallenController::countHoles() const
		{
			int holes = 0;
			for (int i = left; i <= right; i++)
			{
				bool shapeTopFound = false;
				bool previousWasHole = false;
				for (int j = top; j <= bottom; j++)
				{
					if (!fallen.cubeAt(i, j).empty())
					{
						if (!shapeTopFound)
						{
							shapeTopFound = true;
						}
						else
						{
							previousWasHole = false;
						}
					}
					else if (shapeTopFound)
					{
						if (!previousWasHole)
						{
							holes ++;
							previousWasHole = true;
						}
					}

				}
			}
			return holes;
		}

		FallenController::~FallenController()
		{
		}
	}
}
