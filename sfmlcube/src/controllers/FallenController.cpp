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
		FallenController::FallenController(TimingManager& timingManager, WallsController& wallsController, const VelocityController& velocityController,
				                           int top, int fieldBottom, int visibleBottom, int left, int right) :
				TimeDependent(timingManager),
				lines(timingManager),
				fallen(timingManager),
				state(sPassive),
				wallsController(wallsController),
				backgroundDealer(right - left),
				velocityController(velocityController),
				left(left), top(top), right(right), fieldBottom(fieldBottom), visibleBottom(visibleBottom),
				linesBurnt(0),
				linesJustFilled(0)
		{
		}

		void FallenController::processTimeStep(double dt)
		{
			switch (state)
			{
			case sPassive:
				// Do nothing
				break;
			case sBlinking:
				if (!lines.isBurningBlinkingInProgress())
				{
					removeBurntLinesAndStartFallingRemaining();
					state = sFalling;
				}
				break;
			case sFalling:
				if (!lines.isFallingInProgress())
				{
					rebuildShape();
					state = sPassive;
				}
				break;
			}
		}

		bool FallenController::anyCollisionsWithRemainingLines(const ShapeCubes& cubes)
		{
			Shape shape(getTimingManager());		// TODO Strange usage of Shape class. Maybe it should be simplified
			shape.setCubes(cubes);
			ShapeDynamics sd(shape);

			lines.addAllRemainingToShapeDynamics(sd);

			sd.addObstacle(fallen);

			return sd.anyCollisions();
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
				FallenRow* curLine = new FallenRow(getTimingManager(), velocityController, fallen.getCubes(), left, right, j);

				if (!curLine->isEmpty())
				{

					if (j > fieldBottom)
					{
						curLine->setType(FallenRow::tFallingDown);
						lines.give(curLine);
					}
					else if (curLine->lineIsFull())
					{
						if (burningBlockAtBottomEnd)
						{
							curLine->setType(FallenRow::tFallingDown);
							lines.give(curLine);
							linesJustFilledToFlyDown ++;
						}
						else
						{
							curLine->setType(FallenRow::tBurning);
							curLine->setBlink(true);
							lines.give(curLine);
							burningCount++;
						}
					}
					else
					{
						curLine->setFallBy(linesJustFilledToFlyDown + burningCount);
						burningBlockAtBottomEnd = false;

						curLine->setType(FallenRow::tRemaining);
						lines.give(curLine);
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
				FallenRow* newLine = FallenRow::fromDealer(getTimingManager(), velocityController, backgroundDealer, left, right, j);
				newLine->setFallBy(linesJustFilledToFlyDown + burningCount);

				newLine->setType(FallenRow::tRemaining);
				lines.give(newLine);
			}

			// Set movement for flying down lines
			lines.setFallByForFallingDown(linesJustFilledToFlyDown);

			// Extracting the brick-related
			for (int j = fieldBottom; j >= 0; j--)
			{
				FallenRow* fr = lines.editableRowAt(j);
				if (fr != NULL)
				{
					ShapeCubes cubes = fr->getShape().getCubes();
					for (int i = left; i <= right; i++)
					{
						if (cubes.cubeAt(i, j).size() > 0 &&
						    cubes.cubeAt(i, j).back().modelType == Cube::mtWall)
						{
							// Here we've found a wall cube. It should be extracted
							// from it's place with all the cubes above it
							FallenPart* fp = new FallenPart(getTimingManager(), velocityController);
							for (int k = j; k >= 0; k--)
							{
								if (cubes.cubeAt(i, k).size() > 0)
								{
								    Cube theCube = cubes.cubeAt(i, k).back();
								    if (theCube.modelType == Cube::mtWall)
								    {
								    	break;
								    }
								    else
								    {
								    	ShapeCubes sc = fp->editableShape().getCubes();
								    	sc.addCube(theCube);
								    	fp->editableShape().setCubes(sc);

								    	cubes.removeCube(i, k);
								    }
								}
							}

						}
					}
				}
				fr->setFallBy(linesJustFilledToFlyDown);
				columns.push_back(fr);
			}

			// Clearing the source shape
			fallen.clear();

			if (linesJustFilledToFlyDown > 0 || burningCount > 0)
			{
				// Starting the blinking of the firing lines
				lines.startBlinking();
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
			fallen.setCubes(lines.toShapeCubes());
			lines.clear();
		}

		void FallenController::removeBurntLinesAndStartFallingRemaining()
		{
			// Counting burnt lines
			linesJustFilled = lines.countBurningLines() + linesJustFilledToFlyDown;
			linesBurnt += linesJustFilled;

			// Clearing the burnt lines
			lines.removeBurningLines();

			// Start falling down the walls
			wallsController.startFalling(linesJustFilledToFlyDown);
			// Starting falling
			lines.startFalling();

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
