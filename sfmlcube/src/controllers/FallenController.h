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
#include "FallenRows.h"

using namespace sfmlcubes::movingcubes::transitions;

namespace sfmlcubes
{
	namespace controllers
	{
		class FallenController : public sf::NonCopyable, public TimeDependent
		{
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

			FallenRows lines;
			list<FallenPart*> columns;

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
			list<const Shape*> getShapes() const
			{
				list<const Shape*> res;
				res.push_back(&fallen);
				lines.toShapes(res);

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
