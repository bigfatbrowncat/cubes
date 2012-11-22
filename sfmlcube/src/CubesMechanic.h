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

	enum CubesMechanicCommand
	{
		cmcMoveDown = 0,
		cmcMoveDownFast = 1,
		cmcMoveRight = 2,
		cmcMoveLeft = 3,
		cmcRotateCW = 4
	};

	typedef void OrderIssuedNotifier(CubesMechanicCommand order, CubesMechanicIssueResponse response);
	typedef void TransitionFinishedNotifier(CubesMechanicCommand order);
	typedef void BeforeOrderIssuingNotifier();

	class CubesMechanic
	{
		CubesField field;
		CubesGroup walls, falling, fallen;

		CubesMechanicHorizontalDirection horizontalDirection;
		CubesMechanicVerticalDirection verticalDirection;
		CubesMechanicRotationDirection rotationDirection;

		/*bool linesAreFiring;
		float linesFiringPhase;
		list<int> linesToFire;*/
		int linesFired;
/*
		CubesMechanicDiscreteAngle sumRotationValue;

		bool cubeIsEmptyOrFreeAt(int i, int j);*/

/*		float calculateRadius(int rotationCenterX, int rotationCenterY, CubeRotatingCenterType crct);
		int fallingCenterX;
		int fallingCenterY;
		int fallingRadius;
		CubeRotatingCenterType fallingCRCT;*/

		OrderIssuedNotifier* orderIssuedNotifier;
		BeforeOrderIssuingNotifier* beforeOrderIssuingNotifier;
		TransitionFinishedNotifier* transitionFinishedNotifier;

		//list<CubesMechanicOrder> ordersQueue;

		CubesMechanicIssueResponse executeNextOrder();
		//bool ordersStarted;

		bool areAnyCollisions();

		//bool canFireLines();

		void moveDown();
		void moveRight();
		void moveLeft();
		void rotate(CubesMechanicDiscreteAngle angle);

		//void fireLines();

/*		CubesMechanicIssueResponse startMovingDownTransition(bool fast);
		CubesMechanicIssueResponse startMovingRightTransition();
		CubesMechanicIssueResponse startMovingLeftTransition();
		CubesMechanicIssueResponse startRotatingCWTransition();
		CubesMechanicIssueResponse startFiringLinesTransition();*/

/*		void setSliding(float slidingX, float slidingY);
		void setRotation(int centerX, int centerY, CubeRotatingCenterType crct, float angle);
		void setFiringLinesAlpha(float alpha);
		void setFiringLinesSliding(float phase);*/

		bool createTBlock();
/*		bool createJBlock();
		bool createLBlock();
		bool createIBlock();
		bool createZBlock();
		bool createSBlock();
		bool createOBlock();*/
	public:
		CubesMechanic(int width, int height);
		virtual ~CubesMechanic();

		bool canMoveDownFalling();
		bool canMoveRightFalling();
		bool canMoveLeftFalling();
		bool canRotateCWFalling(int angle);

		bool createNewBlock();

		CubesField& getField() { return field; }
		//const CubesField& getFieldBackground() const { return background; }
		CubesMechanicRotationDirection getRotationDirection() const { return rotationDirection; }
		int getLinesFired() const { return linesFired; }

		void setOrderIssuedNotifier(OrderIssuedNotifier& notifier) { orderIssuedNotifier = &notifier; }
		void setBeforeOrderIssuingNotifier(BeforeOrderIssuingNotifier& notifier) { beforeOrderIssuingNotifier = &notifier; }
		void setTransitionFinishedNotifier(TransitionFinishedNotifier& notifier) { transitionFinishedNotifier = &notifier; }

		void fallingToFallen();

		void turnOn(CubesMechanicCommand command);
		void turnOff(CubesMechanicCommand command);

		void issueHighPriorityOrder(CubesMechanicCommand order);

		void processTimeStep(float dt);
		void cleanFrees();

	};

}

#endif /* CUBESMECHANIC_H_ */
