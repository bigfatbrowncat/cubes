/*
 * FallenController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLENCONTROLLER_H_
#define FALLENCONTROLLER_H_

#include "../movingcubes/ShapeContainer.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"
#include "WallsController.h"
#include "../Logger.h"

#include <SFML/System/NonCopyable.hpp>

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		class FallenController : public ShapeContainer, sf::NonCopyable
		{
			class LineWithKinematics : public ShapeContainer, sf::NonCopyable
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
				LineWithKinematics(const VelocityController& velocityController, const Shape& source, int left, int right, int j);

				bool lineIsFull();
				bool lineIsEmpty();

				void setBlink(bool value) { blink = value; }
				bool getBlink() { return blink; }
				void setMoveBy(int value) { moveBy = value; }
				int getMoveBy() { return moveBy; }

				void advanceStep(double delta)
				{
					kinematics.advanceStep(delta);
				}

				bool isBlinkingInProgress()
				{
					return kinematics.getBlinkingTransition().isInProgress();
				}

				bool isMovingInProgress()
				{
					return kinematics.getVerticalTransition().isInProgress();
				}

				void startAnimation()
				{
					if (blink)
					{
						if (kinematics.getBlinkingTransition().isInProgress())
						{
							Logger::DEFAULT.logWarning("try to start blinking twice");
						}

						kinematics.blink(BLINKING_LONGITUDE, 3);
					}

					if (moveBy != 0)
					{
						if (kinematics.getVerticalTransition().isInProgress())
						{
							Logger::DEFAULT.logWarning("try to start moving twice");
						}

						kinematics.moveVertical(moveBy, Transition::ppfParabolic, velocityController.getFallingDownFiredLongitude());
					}
				}

				Shape getShape() const
				{
					return line;
				}
				void setShape(const Shape& shape)
				{
					line = shape;
				}

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
			const VelocityController& velocityController;

			int left, top, right, bottom;
			int linesFired;
			int linesJustFired;

			Shape fallen;

			list<LineWithKinematics*> remainingLines;
			list<LineWithKinematics*> burningLines;
			list<LineWithKinematics*> flyingDownLines;

			void startFalling();
			void startBlinking();

			bool isFallingInProgress();
			bool isBlinkingInProgress();

			void collectLines();
			void rebuildShape();
			void removeBurntLinesAndStartFallingRemaining();



		public:
			FallenController(WallsController& wallsController, const VelocityController& velocityController, int top, int bottom, int left, int right);

			Shape getShape() const
			{
				return fallen;
			}
			void setShape(const Shape& shape) { fallen = shape; }
			list<Shape> getShapes() const
			{
				list<Shape> res;
				res.push_back(fallen);
				for (list<LineWithKinematics*>::const_iterator iter = remainingLines.begin();
					 iter != remainingLines.end();
					 iter++)
				{
					res.push_back((**iter).getShape());
				}
				return res;
			}

			void processTimeStep(float dt);
			bool anyCollisionsWithRemainingLines(const Shape& shape);

			void mergeShape(const Shape& other) { fallen += other; }
			void fireFullLines() { collectLines(); }
			int getLinesFired() const { return linesFired; }
			int getLinesJustFired() const { return linesJustFired; }

			State getState() const { return state; }
			int getWidth() const { return right - left + 1; }
			int getHeight() const { return bottom - top + 1; }
			int countHoles() const;

			virtual ~FallenController();
		};
	}
}
#endif
