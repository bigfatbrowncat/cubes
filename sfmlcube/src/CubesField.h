/*
 * CubesField.h
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#ifndef CUBESFIELD_H_
#define CUBESFIELD_H_

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	enum CubeSlidingDirection
	{
		csdNone = 0, csdUp = 1, csdDown = 2, csdLeft = 3, csdRight = 4
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
		bool falling;
		CubeSlidingDirection slidingDirection;
		CubeRotatingDirection rotatingDirection;
		CubeRotatingCenterType rotatingCenterType;

		int rotatingCenterX, rotatingCenterY;

		// Constructs non-empty cube
		Cube(sf::Color color,
		     bool falling,
		     CubeSlidingDirection slidingDirection = csdNone,
		     CubeRotatingDirection rotatingDirection = crdNone,
		     CubeRotatingCenterType rotatingCenterType = crctCenterOfCube,
		     int rotatingCenterX = 0, int rotatingCenterY = 0):
		     empty(false),
		     color(color),
		     falling(falling),
		     slidingDirection(slidingDirection),
		     rotatingDirection(rotatingDirection),
		     rotatingCenterType(rotatingCenterType),
		     rotatingCenterX(rotatingCenterX),
		     rotatingCenterY(rotatingCenterY)
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
		Cube* cubesData;
		int width, height;
	public:
		CubesField(int width, int height);
		virtual ~CubesField();

		const Cube& getCube(int i, int j);
		void setCube(int i, int j, const Cube& value);

		int getWidth() { return width; }
		int getHeight() { return height; }

		void resetAnimations();
		bool calculateSliding(CubesSlidingType cst);
	};

}

#endif /* CUBESFIELD_H_ */
