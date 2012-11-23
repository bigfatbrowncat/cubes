/*
 * CubesField.h
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */


#ifndef CUBESFIELD_H_
#define CUBESFIELD_H_

#include <list>

#include "CubesGroup.h"
#include "CubeRotatingCenterType.h"

using namespace std;

namespace sfmlcubes
{
	class CubesField : public sf::NonCopyable
	{
	private:
		list<CubesGroup*> cubesGroups;
		int width, height;

	public:
		CubesField(int width, int height): width(width), height(height) {}
		virtual ~CubesField() {}

		void advanceStep(double delta);
		bool anyTransitionsInProgress();

		list<CubesGroup*>& getCubesGroups() { return cubesGroups; }

		list<Cube*> cubeAt(int i, int j);

		int getWidth() const { return width; }
		int getHeight() const { return height; }

		void glDraw(int dx, int dy);
	};

}

#endif
