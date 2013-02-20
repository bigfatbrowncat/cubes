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
		float FallenController::RowWithKinematics::BLINKING_LONGITUDE = 0.6;

		FallenController::RowWithKinematics::RowWithKinematics(const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j) :
				velocityController(velocityController), kinematics(line), left(left), right(right), j(j), blink(false), moveBy(0)
		{
			ShapeCubes lineCubes;
			for (int i = left; i <= right; i++)
			{
				if (!source.cubeAt(i, j).empty())
				{
					// Adding the cube to the current firing group
					if (source.cubeAt(i, j).size() > 1) Logger::DEFAULT.logWarning("cubeAt returned more than one cube");
					lineCubes.addCube(source.cubeAt(i, j).back());
				}
			}
			line.setCubes(lineCubes);
		}

		bool FallenController::RowWithKinematics::lineIsFull()
		{
			for (int i = left; i <= right; i++)
			{
				if (line.getCubes().cubeAt(i, j).empty()) return false;
			}
			return true;
		}

		bool FallenController::RowWithKinematics::lineIsEmpty()
		{
			for (int i = left; i <= right; i++)
			{
				if (!line.getCubes().cubeAt(i, j).empty()) return false;
			}
			return true;
		}

		FallenController::FallenController(WallsController& wallsController, const VelocityController& velocityController,
				                           int top, int fieldBottom, int visibleBottom, int left, int right) :
				state(sPassive),
				wallsController(wallsController),
				backgroundDealer(right - left),
				velocityController(velocityController),
				left(left), top(top), right(right), fieldBottom(fieldBottom), visibleBottom(visibleBottom),
				linesBurnt(0),
				linesJustFilled(0)
		{
		}

		void FallenController::processTimeStep(float dt)
		{
			fallen.processTimeStep(dt);

			for (list<RowWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				(**iter).advanceStep(dt);
			}
			for (list<RowWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				(**iter).advanceStep(dt);
			}
			for (list<RowWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
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

		bool FallenController::anyCollisionsWithRemainingLines(const ShapeCubes& cubes)
		{
			Shape shape;
			shape.setCubes(cubes);
			ShapeDynamics sd(shape);

			for (list<RowWithKinematics*>::const_iterator iter = remainingLines.begin();
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
			for (list<RowWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				(**iter).startAnimation();
			}

			for (list<RowWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
			{
				(**iter).startAnimation();
			}
		}

		void FallenController::startBlinking()
		{
			for (list<RowWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				(**iter).startAnimation();
			}
		}

		bool FallenController::isBlinkingInProgress()
		{
			for (list<RowWithKinematics*>::iterator iter = burningLines.begin(); iter != burningLines.end(); iter++)
			{
				if ((**iter).isBlinkingInProgress()) return true;
			}
			return false;
		}

		bool FallenController::isFallingInProgress()
		{
			for (list<RowWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				if ((**iter).isMovingInProgress()) return true;
			}

			for (list<RowWithKinematics*>::iterator iter = remainingLines.begin(); iter != remainingLines.end(); iter++)
			{
				if ((**iter).isMovingInProgress()) return true;
			}

			return false;
		}

		void FallenController::collectLines()
		{
			bool burningBlockAtBottomEnd = true;
			linesJustFilled = 0;
			linesJustFilledToFlyDown = 0;
			int burningCount = 0;

			// Collecting the lines to lists
			for (int j = visibleBottom; j >= top; j--)
			{
				RowWithKinematics* curLine = new RowWithKinematics(velocityController, fallen.getCubes(), left, right, j);

				if (!curLine->lineIsEmpty())
				{

					if (j > fieldBottom)
					{
						flyingDownLines.push_back(curLine);
					}
					else if (curLine->lineIsFull())
					{
						if (burningBlockAtBottomEnd)
						{
							flyingDownLines.push_back(curLine);
							linesJustFilledToFlyDown ++;
						}
						else
						{
							curLine->setBlink(true);
							burningLines.push_back(curLine);
							burningCount++;
						}
					}
					else
					{
						curLine->setMoveBy(linesJustFilledToFlyDown + burningCount);
						burningBlockAtBottomEnd = false;
						remainingLines.push_back(curLine);
					}
				}
				else
				{
					// current line is empty
					delete curLine;
				}
			}

			// Dealing the new lines
			for (int j = -1; j >= -linesJustFilledToFlyDown; j--)
			{
				RowWithKinematics* newLine = RowWithKinematics::fromDealer(velocityController, backgroundDealer, left, right, j);
				newLine->setMoveBy(linesJustFilledToFlyDown + burningCount);
				remainingLines.push_back(newLine);
			}

			// Set movement for flying down lines
			for (list<RowWithKinematics*>::iterator iter = flyingDownLines.begin(); iter != flyingDownLines.end(); iter++)
			{
				(*iter)->setMoveBy(linesJustFilledToFlyDown);
			}

			// Clearing the source shape
			fallen.clear();

			if (linesJustFilledToFlyDown > 0 || burningCount > 0)
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
				ShapeCubes fallenCubes = fallen.getCubes();
				fallenCubes += burningLines.back()->getShape().getCubes();
				fallen.setCubes(fallenCubes);

				delete burningLines.back();
				burningLines.pop_back();
			}
			while (flyingDownLines.size() > 0)
			{
				ShapeCubes fallenCubes = fallen.getCubes();
				fallenCubes += flyingDownLines.back()->getShape().getCubes();
				fallen.setCubes(fallenCubes);

				delete flyingDownLines.back();
				flyingDownLines.pop_back();
			}
			while (remainingLines.size() > 0)
			{
				ShapeCubes fallenCubes = fallen.getCubes();
				fallenCubes += remainingLines.back()->getShape().getCubes();
				fallen.setCubes(fallenCubes);

				delete remainingLines.back();
				remainingLines.pop_back();
			}
		}

		void FallenController::removeBurntLinesAndStartFallingRemaining()
		{
			// Counting burnt lines
			linesJustFilled = burningLines.size() + linesJustFilledToFlyDown;
			linesBurnt += linesJustFilled;

			// Clearing the burnt lines
			burningLines.clear();

			// Start falling down the walls
			wallsController.startFalling(linesJustFilledToFlyDown);
			// Starting falling
			startFalling();

			{
				stringstream ss;
				ss << "Just cleared: " << linesJustFilled << " lines";
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
				for (int j = top; j <= fieldBottom; j++)
				{
					if (!fallen.getCubes().cubeAt(i, j).empty())
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
