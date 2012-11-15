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

		     rotatingCenterX(0),
		     rotatingCenterY(0),
		     rotatingAngle(0)
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

		void glDraw();
	};

}

#endif /* CUBESFIELD_H_ */
