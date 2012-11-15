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
		cmvdDown,
		cmvdDownFast
	};
	enum CubesMechanicRotationDirection
	{
		cmrdNone,
		cmrdCW,
		cmrdCCW
	};

	class CubesMechanic
	{
		struct RotationData
		{
			int x, y;
			int R;
			CubeRotatingCenterType crct;
		};

		static float ROTATION_LONGITUDE;
		static float FALLING_DOWN_LONGITUDE;
		static float FALLING_DOWN_FAST_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;

		CubesField field;

		CubesMechanicVerticalDirection verticalMovingDirection;
		float verticalMovingPhase;	// 0..1

		CubesMechanicHorizontalDirection horizontalMovingDirection;
		float horizontalMovingPhase;

		CubesMechanicRotationDirection rotationDirection;
		float rotationPhase;

		bool cubeIsEmptyOrFreeAt(int i, int j);
		RotationData findCenter();
	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		bool canMoveDown();
		bool canMoveRight();
		bool canMoveLeft();
		bool canRotate();

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotate(int angle);

		CubesMechanicIssueResponse issueMovingDown(bool fast);
		CubesMechanicIssueResponse issueMovingRight();
		CubesMechanicIssueResponse issueMovingLeft();
		CubesMechanicIssueResponse issueRotatingCW();

		void processTimeStep(float dt);

		void setSliding(float slidingX, float slidingY);
		void setRotation(int centerX, int centerY, CubeRotatingCenterType crct, float angle);

		void cleanFrees();
		void createNewBlock();

		const CubesField& getField() const { return field; }
		CubesMechanicHorizontalDirection getHorizontalDirection() const { return horizontalMovingDirection; }
		CubesMechanicRotationDirection getRotationDirection() const { return rotationDirection; }


		// ***************
		void test_createBlueCube();
	};

}

#endif /* CUBESMECHANIC_H_ */
