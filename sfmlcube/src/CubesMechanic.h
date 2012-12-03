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

#include "movingcubes/ShapeKinematics.h"
#include "movingcubes/ShapeDynamics.h"

#include "WallsController.h"
#include "FallenController.h"
#include "FallingShapeController.h"
#include "ShapeDealer.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
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

	class CubesMechanic
	{
		int width, height;
		CubesMechanicState state;

		WallsController wallsController;
		FallenController fallenController;
		VelocityController velocityController;
		FallingShapeController fallingShapeController;
		ShapeDealer shapeDealer;

		double time;
		double momentWhenFallIssued;
		bool paused;

	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		const ShapeDealer& getShapeDealer() const { return shapeDealer; }

		int getWidth() const { return width; }
		int getHeight() const { return height; }

		void turnOn(CubesMechanicCommand command);
		void turnOff(CubesMechanicCommand command);

		void issueHighPriorityOrder(CubesMechanicCommand order);

		void processTimeStep(float dt);
		void cleanFrees();

		CubesMechanicState getState() const { return state; }
		int getLinesFired() const { return fallenController.getLinesFired(); }
		float getVelocityMultiplicator() const { return velocityController.getVelocityMultiplicator(); }

		bool isPaused() { return paused; }

		void glDraw(int dx, int dy);
	};

}

#endif /* CUBESMECHANIC_H_ */
