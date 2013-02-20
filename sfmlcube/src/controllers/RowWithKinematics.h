/*
 * RowWithKinematics.h
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#ifndef ROWWITHKINEMATICS_H_
#define ROWWITHKINEMATICS_H_

#include "VelocityController.h"
#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeCubes.h"
#include "../movingcubes/ShapeKinematics.h"
#include "BackgroundDealer.h"
#include "../Logger.h"
#include "../movingcubes/transitions/ParabolicPhaseProcessingFunction.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
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

	}
}
#endif
