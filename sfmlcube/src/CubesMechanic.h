/*
 * CubesMechanic.h
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#ifndef CUBESMECHANIC_H_
#define CUBESMECHANIC_H_

#include <list>

#include "CubesField.h"

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
		static float FALLING_PERIOD;

		CubesMechanicState state;

		CubesField field;
		CubesGroup walls, falling, fallen;

		CubesMechanicHorizontalDirection horizontalDirection;
		CubesMechanicVerticalDirection verticalDirection;
		CubesMechanicRotationDirection rotationDirection;

		/*bool linesAreFiring;
		float linesFiringPhase;*/
		list<int> linesToFire;
		list<CubesGroup*> firingGroups;
		int linesFired;
		double time;
		double momentWhenFallIssued;
/*
		CubesMechanicDiscreteAngle sumRotationValue;

		bool cubeIsEmptyOrFreeAt(int i, int j);*/

/*		float calculateRadius(int rotationCenterX, int rotationCenterY, CubeRotatingCenterType crct);
		int fallingCenterX;
		int fallingCenterY;
		int fallingRadius;
		CubeRotatingCenterType fallingCRCT;*/

		bool anyCollisions();
		void firingGroupsToFallen();

		//bool countLinesToFire();

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotate(CubesMechanicDiscreteAngle angle);

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

		bool canMoveDownFalling();
		bool canMoveRightFalling();
		bool canMoveLeftFalling();
		bool canRotateCWFalling(CubesMechanicDiscreteAngle angle);

		void moveDownFiredFalling();

		void fireLines();
		bool createNewBlock();

		CubesField& getField() { return field; }
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
		const CubesGroup& getFalling() const { return falling; }

	};

}

#endif /* CUBESMECHANIC_H_ */
