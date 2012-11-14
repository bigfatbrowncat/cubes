/*
 * CubesField.h
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <vector>

using namespace std;

#ifndef CUBESFIELD_H_
#define CUBESFIELD_H_

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	enum CubeVerticalSlidingDirection
	{
		cvsdNone = 0, cvsdUp = 1, cvsdDown = 2
	};
	enum CubeHorizontalSlidingDirection
	{
		chsdNone = 0, chsdLeft = 1, chsdRight = 2
	};
	enum CubeRotatingDirection
	{
		crdNone, crdCW, crdCCW
	};
	enum CubeRotatingCenterType
	{
		crctCenterOfCube, crctCornerOfCube
	};

	struct Cube
	{
		bool empty;
		sf::Color color;
		bool freeMoving;

		// Vertical sliding animation
		CubeVerticalSlidingDirection verticalSlidingDirection;
		float verticalSlidingPhase;

		// Horizontal sliding animation
		CubeHorizontalSlidingDirection horizontalSlidingDirection;
		float horizontalSlidingPhase;

		// Rotating animation
		CubeRotatingDirection rotatingDirection;
		CubeRotatingCenterType rotatingCenterType;
		int rotatingCenterX, rotatingCenterY;
		float rotatingPhase;

		// Constructs non-empty cube
		Cube(sf::Color color, bool falling):
		     empty(false),
		     color(color),
		     freeMoving(falling),

		     verticalSlidingDirection(cvsdNone),
		     verticalSlidingPhase(0),

		     horizontalSlidingDirection(chsdNone),
		     horizontalSlidingPhase(0),

		     rotatingCenterX(0),
		     rotatingCenterY(0)
		{

		}

		// Constructs empty cube
		Cube(): empty(true) {}
	};

	enum CubesSlidingType
	{
		cstSlidingAnimation,
		cstTrueSliding
	};

	class CubesField
	{
	private:
		struct XY
		{
			int x, y;
			XY(int x, int y): x(x), y(y) {}
		};

		Cube* cubesData;
		int width, height;

	public:
		CubesField(int width, int height);
		virtual ~CubesField();

		Cube& getCube(int i, int j);
		void setCube(int i, int j, const Cube& value);

		int getWidth() { return width; }
		int getHeight() { return height; }

		bool calculateFalling(CubesSlidingType cst);
		bool tryMoveRight(CubesSlidingType cst);
	};

}

#endif /* CUBESFIELD_H_ */
