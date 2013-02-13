/*
 * WallsController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef WALLSCONTROLLER_H_
#define WALLSCONTROLLER_H_

#include "../movingcubes/Shape.h"
#include "../movingcubes/ShapeContainer.h"
#include "../movingcubes/ShapeKinematics.h"
#include "VelocityController.h"
#include "BackgroundDealer.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class WallsController : public ShapeContainer
		{
			enum State
			{
				sIdle,
				sMovingDown
			};

			const VelocityController& velocityController;

			Shape walls;
			ShapeKinematics wallsKinematics;
			BackgroundDealer backgroundDealer;

			State state;
			int width, height, visibleFrame;

			sf::Color wallColor;

			void addTopBricks(int count);
			void addRowsFromDealer(int count);

		public:
			WallsController(const VelocityController& velocityController, int width, int height, int visibleFrame);

			void processTimeStep(float dt);

			Shape getShape() const { return walls; }
			void setShape(const Shape& shape) { walls = shape; }

			void startFalling(int count);

			virtual ~WallsController();
		};
	}
}
#endif
