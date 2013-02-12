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
			State state;
			int width, height, visibleHeight;

			sf::Color wallColor;

			void addTopBricks(int count);

		public:
			WallsController(const VelocityController& velocityController, int width, int height, int visibleHeight);

			void processTimeStep(float dt);

			Shape getShape() const { return walls; }
			void setShape(const Shape& shape) { walls = shape; }

			void startFalling(int count);

			virtual ~WallsController();
		};
	}
}
#endif
