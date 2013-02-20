/*
 * WallsController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef WALLSCONTROLLER_H_
#define WALLSCONTROLLER_H_

#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeKinematics.h"
#include "VelocityController.h"
#include "BackgroundDealer.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class WallsController : public TimeDependent
		{
			enum State
			{
				sIdle,
				sMovingDown
			};

			const VelocityController& velocityController;

			Shape walls;
			ShapeKinematics wallsKinematics;

			State state;
			int width, height, visibleFrame;

			sf::Color wallColor;

			void addTopBricks(int count);

		public:
			WallsController(TimingManager& timingManager, const VelocityController& velocityController, int width, int height, int visibleFrame);

			void processTimeStep(double dt);

			const Shape& getShape() const { return walls; }

			void startFalling(int count);

			bool anyCollisions(const ShapeCubes& shape);

			virtual ~WallsController();
		};
	}
}
#endif
