/*
 * FallenController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLENCONTROLLER_H_
#define FALLENCONTROLLER_H_

#include <SFML/System/NonCopyable.hpp>

#include "../movingcubes/transitions/ParabolicPhaseProcessingFunction.h"
#include "../movingcubes/transitions/ArctangentPhaseProcessingFunction.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"
#include "WallsController.h"
#include "../Logger.h"

using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace controllers
	{
		class FallenController : public sf::NonCopyable, public TimeDependent
		{
			class RowWithKinematics : public sf::NonCopyable
			{
				static float BLINKING_LONGITUDE;

			private:
				const VelocityController& velocityController;

				Shape line;
				ShapeKinematics kinematics;
				int left, right, j;
				bool blink;
				int moveBy;

			public:
				RowWithKinematics(TimingManager& timingManager, const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j);
				static RowWithKinematics* fromDealer(TimingManager& timingManager, const VelocityController& velocityController, BackgroundDealer& backgroundDealer, int left, int right, int j)
				{
					ShapeCubes shp;
					backgroundDealer.setWidth(right - left + 1);
					vector<BackgroundDealer::CellType> newRow = backgroundDealer.dealRow();
					for (size_t i = 0; i < newRow.size(); i++)
					{
						switch (newRow[i])
						{
						case BackgroundDealer::ctEmpty:
							// add nothing
							break;
						case BackgroundDealer::ctWall:
							// add wall
							shp.addCube(Cube(i + left, j, Cube::mtWall, sf::Color(128, 128, 128)));
							break;
						default:
							Logger::DEFAULT.logWarning("Strange case here...");
							break;
						}
					}
					return new RowWithKinematics(timingManager, velocityController, shp, left, right, j);
				}

				bool lineIsFull();
				bool lineIsEmpty();

				void setBlink(bool value) { blink = value; }
				bool getBlink() { return blink; }
				void setMoveBy(int value) { moveBy = value; }
				int getMoveBy() { return moveBy; }

				bool isBlinkingInProgress()
				{
					return kinematics.isBlinking();
				}

				bool isMovingInProgress()
				{
					return kinematics.isMovingVertically();
				}

				void startAnimation()
				{
					if (blink)
					{
						if (kinematics.isBlinking())
						{
							Logger::DEFAULT.logWarning("try to start blinking twice");
						}

						kinematics.blink(BLINKING_LONGITUDE, 3);
					}

					if (moveBy != 0)
					{
						if (kinematics.isMovingVertically())
						{
							Logger::DEFAULT.logWarning("try to start moving twice");
						}

						kinematics.moveVertical(moveBy, ParabolicPhaseProcessingFunction(), velocityController.getFallingDownFiredDuration());
					}
				}

				const Shape& getShape() const
				{
					return line;
				}

				virtual ~RowWithKinematics() {}
			};

		public:
			enum State
			{
				sPassive,
				sBlinking,
				sFalling
			};
		private:
			State state;

			WallsController& wallsController;
			BackgroundDealer backgroundDealer;

			const VelocityController& velocityController;

			int left, top, right, fieldBottom, visibleBottom;
			int linesBurnt;
			int linesJustFilled;

			int linesJustFilledToFlyDown;

			Shape fallen;

			list<RowWithKinematics*> remainingLines;
			list<RowWithKinematics*> burningLines;
			list<RowWithKinematics*> flyingDownLines;

			void startFalling();
			void startBlinking();

			bool isFallingInProgress();
			bool isBlinkingInProgress();

			void collectLines();
			void rebuildShape();
			void removeBurntLinesAndStartFallingRemaining();

			void addRowsFromDealer(int count);

		protected:
			void processTimeStep(double dt);

		public:
			FallenController(TimingManager& timingManager, WallsController& wallsController, const VelocityController& velocityController,
			                 int top, int fieldBottom, int visibleBottom, int left, int right);

			const Shape& getShape() const
			{
				return fallen;
			}
			//void setShape(const Shape& shape) { fallen = shape; }
			list<Shape> getShapes() const
			{
				list<Shape> res;
				res.push_back(fallen);

				for (list<RowWithKinematics*>::const_iterator iter = remainingLines.begin();
					 iter != remainingLines.end();
					 iter++)
				{
					res.push_back((**iter).getShape());
				}

				for (list<RowWithKinematics*>::const_iterator iter = flyingDownLines.begin();
					 iter != flyingDownLines.end();
					 iter++)
				{
					res.push_back((**iter).getShape());
				}

				for (list<RowWithKinematics*>::const_iterator iter = burningLines.begin();
					 iter != burningLines.end();
					 iter++)
				{
					res.push_back((**iter).getShape());
				}

				return res;
			}

			bool anyCollisionsWithRemainingLines(const ShapeCubes& cubes);

			void fireFullLines() { collectLines(); }
			int getLinesFired() const { return linesBurnt; }
			int getLinesJustBurnt() const { return linesJustFilled; }

			State getState() const { return state; }
			int getWidth() const { return right - left + 1; }
			int getFieldHeight() const { return fieldBottom - top + 1; }
			int countHoles() const;

			void mergeShape(const ShapeCubes& cubes)
			{
				ShapeCubes sc = fallen.getCubes();
				fallen.setCubes(sc += cubes);
			}

			virtual ~FallenController();
		};
	}
}
#endif
