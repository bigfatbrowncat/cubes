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
	enum CubesMechanicIssueResponse
	{
		cmirSuccess,
		cmirAlreadyInProgress,
		cmirFail,
		cmirNothingToIssue
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

	enum CubesMechanicDiscreteAngle
	{
		cmda0		= 0,
		cmda90CW	= 1,
		cmda180CW	= 2,
		cmda270CW	= 3
	};

	enum CubesMechanicOrder
	{
		cmoMoveDown,
		cmoMoveDownFast,
		cmoMoveRight,
		cmoMoveLeft,
		cmoRotateCW,
		cmoFireLines
	};

	typedef void OrderIssuedNotifier(CubesMechanicOrder order, CubesMechanicIssueResponse response);
	typedef void TransitionFinishedNotifier(CubesMechanicOrder order);
	typedef void BeforeOrderIssuingNotifier();

	class CubesMechanic
	{
		struct CenterAndRadiusData
		{
			int x, y;
			int R;
			CubeRotatingCenterType crct;
		};

		static float ROTATION_LONGITUDE;
		static float FALLING_DOWN_LONGITUDE;
		static float FALLING_DOWN_FAST_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;
		static float LINES_FIRING_LONGITUDE;
		static float LINES_FIRING_BLINKING_PART;

		CubesField field;

		CubesMechanicVerticalDirection verticalMovingDirection;
		float verticalMovingPhase;	// 0..1

		CubesMechanicHorizontalDirection horizontalMovingDirection;
		float horizontalMovingPhase;

		CubesMechanicRotationDirection rotationDirection;
		float rotationPhase;

		bool linesAreFiring;
		float linesFiringPhase;
		list<int> linesToFire;

		CubesMechanicDiscreteAngle sumRotationValue;

		bool cubeIsEmptyOrFreeAt(int i, int j);

		float calculateRadius(int rotationCenterX, int rotationCenterY, CubeRotatingCenterType crct);
		int fallingCenterX;
		int fallingCenterY;
		int fallingRadius;
		CubeRotatingCenterType fallingCRCT;

		OrderIssuedNotifier* orderIssuedNotifier;
		BeforeOrderIssuingNotifier* beforeOrderIssuingNotifier;
		TransitionFinishedNotifier* transitionFinishedNotifier;

		list<CubesMechanicOrder> ordersQueue;

		CubesMechanicIssueResponse executeNextOrder();
		bool ordersStarted;

		bool canMoveDown();
		bool canMoveRight();
		bool canMoveLeft();
		bool canRotate();
		bool canFireLines();

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotate(CubesMechanicDiscreteAngle angle);
		void fireLines();

		CubesMechanicIssueResponse startMovingDownTransition(bool fast);
		CubesMechanicIssueResponse startMovingRightTransition();
		CubesMechanicIssueResponse startMovingLeftTransition();
		CubesMechanicIssueResponse startRotatingCWTransition();
		CubesMechanicIssueResponse startFiringLinesTransition();

		void setSliding(float slidingX, float slidingY);
		void setRotation(int centerX, int centerY, CubeRotatingCenterType crct, float angle);
		void setFiringLinesAlpha(float alpha);
		void setFiringLinesSliding(float phase);

		void createTBlock();
		void createJBlock();
		void createLBlock();
		void createIBlock();
		void createZBlock();
		void createSBlock();
		void createOBlock();
	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		void createNewBlock();

		const CubesField& getField() const { return field; }
		CubesMechanicHorizontalDirection getHorizontalDirection() const { return horizontalMovingDirection; }
		CubesMechanicRotationDirection getRotationDirection() const { return rotationDirection; }

		void setOrderIssuedNotifier(OrderIssuedNotifier& notifier) { orderIssuedNotifier = &notifier; }
		void setBeforeOrderIssuingNotifier(BeforeOrderIssuingNotifier& notifier) { beforeOrderIssuingNotifier = &notifier; }
		void setTransitionFinishedNotifier(TransitionFinishedNotifier& notifier) { transitionFinishedNotifier = &notifier; }

		void issueOrder(CubesMechanicOrder order);
		void issueHighPriorityOrder(CubesMechanicOrder order);

		void processTimeStep(float dt);
		void cleanFrees();

	};

}

#endif /* CUBESMECHANIC_H_ */
