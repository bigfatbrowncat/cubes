/*
 * CubesMechanic.h
 *
 *  Created on: Nov 15, 2012
 *      Author: imizus
 */

#ifndef CUBESMECHANIC_H_
#define CUBESMECHANIC_H_

#include "CubesField.h"

namespace sfmlcubes
{
	enum CubesMechanicIssueResponse
	{
		cmirSuccess,
		cmirAlreadyInProgress,
		cmirCantBecauseObstacle
	};

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
		cmvdDown
	};

	class CubesMechanic
	{
		static float FALLING_DOWN_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;

		CubesField field;

		CubesMechanicVerticalDirection verticalMovingDirection;
		float verticalMovingPhase;	// 0..1

		CubesMechanicHorizontalDirection horizontalMovingDirection;
		float horizontalMovingPhase;

		bool cubeIsEmptyOrFreeAt(int i, int j);

	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		bool canMoveDown();
		bool canMoveRight();
		bool canMoveLeft();
		void moveDown();
		void moveRight();
		void moveLeft();

		CubesMechanicIssueResponse issueMovingDown();
		CubesMechanicIssueResponse issueMovingRight();
		CubesMechanicIssueResponse issueMovingLeft();

		void processTimeStep(float dt);
		void setSliding(float slidingX, float slidingY);
		void cleanFrees();

		void createNewBlock();

		const CubesField& getField() const { return field; }
		CubesMechanicHorizontalDirection getHorizontalDirection() const { return horizontalMovingDirection; }


		// ***************
		void test_createBlueCube();
	};

}

#endif /* CUBESMECHANIC_H_ */
