/*
 * CubesMechanic.h
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#ifndef CUBESMECHANIC_H_
#define CUBESMECHANIC_H_

#include <list>
#include <map>

#include "../movingcubes/ShapeKinematics.h"
#include "../movingcubes/ShapeDynamics.h"

#include "WallsController.h"
#include "FallenController.h"
#include "FallingShapeController.h"
#include "ShapeDealer.h"
#include "ScoreCounter.h"

#include "../widgets/CubePainter.h"
#include "../widgets/ShapePainter.h"

namespace sfmlcubes
{
	using namespace movingcubes;
	using namespace widgets;

	namespace controllers
	{
		enum CubesMechanicCommand
		{
			cmcMoveDownFast = 1,
			cmcMoveRight = 2,
			cmcMoveLeft = 3,
			cmcRotateCW = 4,
			cmcPause = 5
		};

		enum CubesMechanicState
		{
			cmsShapeFalling,
			cmsBetweenShapes,
			cmsGameOver
		};

		class CubesField
		{
			int width, height;
			CubesMechanicState state;

			VelocityController velocityController;
			WallsController wallsController;
			FallenController fallenController;
			FallingShapeController fallingShapeController;

			ShapeDealer shapeDealer;
			ScoreCounter scoreCounter;

			double time;
			double momentWhenFallIssued;
			bool paused;

			Shape findProperPosition(const Shape& shape);

		public:
			CubesField(int width, int height, int visibleFrame);
			virtual ~CubesField();

			const ShapeDealer& getShapeDealer() const { return shapeDealer; }
			const WallsController& getWallsController() const { return wallsController; }
			const FallingShapeController& getFallingShapeController() const { return fallingShapeController; }
			const FallenController& getFallenController() const { return fallenController; }

			int getWidth() const { return width; }
			int getHeight() const { return height; }

			void turnOn(CubesMechanicCommand command);
			void turnOff(CubesMechanicCommand command);

			void processTimeStep(float dt);

			CubesMechanicState getState() const { return state; }
			int getLinesFired() const { return fallenController.getLinesFired(); }
			const ScoreCounter& getScoreCounter() const { return scoreCounter; }
			int getVelocityIndex() const
			{
				// Every 20% of velocity is a new level ( 120% -> 2, 140% -> 3 ... )
				return (int)((velocityController.getVelocityMultiplicator() - 1) * 5 + 1);
			}

			bool isPaused() const { return paused; }

		};
	}
}

#endif /* CUBESMECHANIC_H_ */
