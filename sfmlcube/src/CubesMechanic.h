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

#include "movingcubes/Field.h"
#include "movingcubes/ShapeKinematics.h"
#include "movingcubes/ShapeDynamics.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	enum CubesMechanicHorizontalDirection
	{
		cmhdNone,
		cmhdLeft,
		cmhdRight
	};
	enum CubesMechanicVerticalDirection
	{
		cmvdNone,
		cmvdUp,
		cmvdDown,
		cmvdDownFast
	};
	enum CubesMechanicRotationDirection
	{
		cmrdNone,
		cmrdCW,
		cmrdCCW
	};

	enum CubesMechanicCommand
	{
		cmcMoveDown = 0,
		cmcMoveDownFast = 1,
		cmcMoveRight = 2,
		cmcMoveLeft = 3,
		cmcRotateCW = 4
	};

	enum CubesMechanicState
	{
		cmsShapeFalling,
		cmsLinesToFireBlinking,
		cmsLinesFiring,
		cmsGameOver
	};

	class CubesMechanic
	{
		static float ROTATION_LONGITUDE;
		static float FALLING_DOWN_LONGITUDE;
		static float FALLING_DOWN_FAST_LONGITUDE;
		static float FALLING_DOWN_FIRED_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;
		static float BLINKING_LONGITUDE;
		static float FALLING_PERIOD;

		CubesMechanicState state;

		ShapeDynamics fallingDynamics;
		ShapeKinematics fallingKinematics;
		ShapeKinematics fallenKinematics;
		Field field;
		Shape walls, falling, fallen;

		CubesMechanicHorizontalDirection horizontalDirection;
		CubesMechanicVerticalDirection verticalDirection;
		CubesMechanicRotationDirection rotationDirection;

		/*bool linesAreFiring;
		float linesFiringPhase;*/
		list<int> linesToFire;
		list<Shape*> firingGroups;
		list<ShapeKinematics*> firingGroupsDynamics;
		map<ShapeKinematics*, int> firingLineCounts;
		int linesFired;
		double time;
		double momentWhenFallIssued;

		bool anyCollisions();
		void firingGroupsToFallen();

		//bool countLinesToFire();

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotate(int angle);

		bool createTBlock();
		bool createJBlock();
		bool createLBlock();
		bool createIBlock();
		bool createZBlock();
		bool createSBlock();
		bool createOBlock();
	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		void moveDownFiredFalling();

		void collectLinesToFire();
		void removeFiredAwayLines();
		bool anyFiringTransitionsInProgress();
		bool createNewBlock();

		Field& getField() { return field; }
		//const CubesField& getFieldBackground() const { return background; }
		CubesMechanicRotationDirection getRotationDirection() const { return rotationDirection; }
		int getLinesFired() const { return linesFired; }

		void freezeFalling();

		void turnOn(CubesMechanicCommand command);
		void turnOff(CubesMechanicCommand command);

		void issueHighPriorityOrder(CubesMechanicCommand order);

		void processTimeStep(float dt);
		void cleanFrees();

		CubesMechanicState getState() const { return state; }
		const Shape& getFalling() const { return falling; }

	};

}

#endif /* CUBESMECHANIC_H_ */
