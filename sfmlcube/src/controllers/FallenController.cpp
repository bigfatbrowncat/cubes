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
		float FallenController::LineWithKinematics::BLINKING_LONGITUDE = 0.6;

		FallenController::LineWithKinematics::LineWithKinematics(const VelocityController& velocityController, const Shape& source, int left, int right, int j) :
				velocityController(velocityController), kinematics(*this), left(left), right(right), j(j), blink(false), moveBy(0)
		{
			for (int i = left; i <= right; i++)
			{
				if (!source.cubeAt(i, j).empty())
				{
					// Adding the cube to the current firing group
					if (source.cubeAt(i, j).size() > 1) Logger::DEFAULT.logWarning("cubeAt returned more than one cube");
					line.addCube(source.cubeAt(i, j).back());
				}
			}
		}

		bool FallenController::LineWithKinematics::lineIsFull()
		{
			for (int i = left; i <= right; i++)
			{
				if (line.cubeAt(i, j).empty()) return false;
			}
			return true;
		}

		bool FallenController::LineWithKinematics::lineIsEmpty()
		{
			for (int i = left; i <= right; i++)
			{
				if (!line.cubeAt(i, j).empty()) return false;
			}
			return true;
		}

		FallenController::FallenController(WallsController& wallsController, const VelocityController& velocityController, int left, int top, int right, int bottom) :
				state(sPassive),
				wallsController(wallsController),
				velocityController(velocityController),
				left(left), top(top), right(right), bottom(bottom),
				linesFired(0),
				linesJustFired(0)
		{
		}

		void FallenController::processTimeStep(float dt)
		{
			for (list<LineWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				(**iter).advanceStep(dt);
			}
			for (list<LineWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				(**iter).advanceStep(dt);
			}
			for (list<LineWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
			{
				(**iter).advanceStep(dt);
			}

			switch (state)
			{
			case sPassive:
				// Do nothing
				break;
			case sBlinking:
				if (!isBlinkingInProgress())
				{
					removeBurntLinesAndStartFallingRemaining();
					wallsController.moveDown();
					state = sFalling;
				}
				break;
			case sFalling:
				if (!isFallingInProgress())
				{
					rebuildShape();
					state = sPassive;
				}
				break;
			}
		}

		bool FallenController::anyCollisionsWithRemainingLines(const Shape& shape)
		{
			ShapeDynamics sd(shape);

			for (list<LineWithKinematics*>::const_iterator iter = remainingLines.begin();
				 iter != remainingLines.end();
				 iter ++)
			{
				sd.addObstacle((**iter).getShape());
			}
			sd.addObstacle(fallen);

			return sd.anyCollisions();
		}

		void FallenController::startFalling()
		{
			for (list<LineWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				(**iter).startAnimation();
			}

			for (list<LineWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
			{
				(**iter).startAnimation();
			}
		}

		void FallenController::startBlinking()
		{
			for (list<LineWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				(**iter).startAnimation();
			}
		}

		bool FallenController::isBlinkingInProgress()
		{
			for (list<LineWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				if ((**iter).isBlinkingInProgress()) return true;
			}
			return false;
		}

		bool FallenController::isFallingInProgress()
		{
			for (list<LineWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				if ((**iter).isMovingInProgress()) return true;
			}

			for (list<LineWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
			{
				if ((**iter).isMovingInProgress()) return true;
			}

			return false;
		}

		void FallenController::collectLines()
		{
			bool burningBlockAtBottomEnd = true;
			int flyingDownCount = 0;
			int burningCount = 0;

			// Collecting the lines to lists
			for (int j = bottom; j >= top; j--)
			{
				LineWithKinematics* curLine = new LineWithKinematics(velocityController, fallen, left, right, j);
				if (curLine->lineIsFull())
				{
					if (burningBlockAtBottomEnd)
					{
						flyingDownLines.push_back(curLine);
						flyingDownCount ++;
					}
					else
					{
						curLine->setBlink(true);
						burningLines.push_back(curLine);
						burningCount++;
					}
				}
				else if (!curLine->lineIsEmpty())
				{
					curLine->setMoveBy(flyingDownCount + burningCount);
					burningBlockAtBottomEnd = false;
					remainingLines.push_back(curLine);
				}
			}

			// Clearing the source shape
			fallen.clear();

			if (flyingDownCount > 0 || burningCount > 0)
			{
				// Starting the blinking of the firing lines
				startBlinking();
				state = sBlinking;
			}
			else
			{
				// Nothing to burn
				rebuildShape();
				state = sPassive;
			}
		}

		void FallenController::rebuildShape()
		{
			fallen.clear();
			while (burningLines.size() > 0)
			{
				fallen += (*burningLines.end())->getShape();
				//delete (*burningLines.end());
				burningLines.pop_back();
			}
			while (flyingDownLines.size() > 0)
			{
				fallen += (*flyingDownLines.end())->getShape();
				//delete (*flyingDownLines.end());
				flyingDownLines.pop_back();
			}
			while (remainingLines.size() > 0)
			{
				LineWithKinematics* end = remainingLines.back();
				fallen += end->getShape();
				//delete end;
				remainingLines.pop_back();
			}
		}

		void FallenController::removeBurntLinesAndStartFallingRemaining()
		{
			// Counting burnt lines
			linesJustFired = burningLines.size();
			linesFired += linesJustFired;

			// Clearing the burnt lines
			burningLines.clear();

			// Starting falling
			startFalling();

			{
				stringstream ss;
				ss << "Just cleared: " << linesJustFired << " lines";
				Logger::DEFAULT.logInfo(ss.str());
			}

			state = sFalling;
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
