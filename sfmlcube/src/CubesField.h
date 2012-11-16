/*
 * CubesField.h
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */

#include <vector>

#include <SFML/Graphics/Shader.hpp>

using namespace std;

#ifndef CUBESFIELD_H_
#define CUBESFIELD_H_

#include <SFML/Graphics.hpp>

namespace sfmlcubes
{
	class CubesField;

	enum CubeRotatingCenterType
	{
		crctCenterOfCube, crctCornerOfCube
	};

	struct Cube
	{
		friend class CubesField;
	protected:
		void glDraw(int i, int j);
	public:

		static const Cube EMPTY;

		static int cubesize;
		static int OBJECT_INDEX;
		static sf::Shader cubeShader;

		static void initGlobal();

		bool empty;
		sf::Color color;
		bool freeMoving;

		// Sliding
		float slidingX, slidingY;

		// Rotating animation
		CubeRotatingCenterType rotatingCenterType;
		int rotatingCenterX, rotatingCenterY;
		float rotatingAngle;	// 1 = 90 degrees

		// Constructs non-empty cube
		Cube(sf::Color color, bool falling):
		     empty(false),
		     color(color),
		     freeMoving(falling),

		     slidingX(0),
		     slidingY(0),

		     rotatingCenterType(crctCenterOfCube),
		     rotatingCenterX(0),
		     rotatingCenterY(0),
		     rotatingAngle(0)
		{

		}

		// Constructs empty cube
		Cube():
			empty(true),
			color(color),
			freeMoving(false),

			slidingX(0),
			slidingY(0),

			rotatingCenterType(crctCenterOfCube),
			rotatingCenterX(0),
			rotatingCenterY(0),
			rotatingAngle(0)
		{

		}

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
		bool* occupiedMap;
		int width, height;

	public:
		CubesField(int width, int height);
		virtual ~CubesField();

		Cube& cubeAt(int i, int j);

		int getWidth() const { return width; }
		int getHeight() const { return height; }

		void glDraw() const;

		bool* getOccupiedMap() {}
	};

}

#endif /* CUBESFIELD_H_ */
