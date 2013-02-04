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
			int width, height;

			void startMovingDown();

		public:
			WallsController(const VelocityController& velocityController, int width, int height);

			void processTimeStep(float dt);

			const Shape& getShape() const { return walls; }
			void setShape(const Shape& shape) { walls = shape; }

			void moveDown();

			virtual ~WallsController();
		};
	}
}
#endif
