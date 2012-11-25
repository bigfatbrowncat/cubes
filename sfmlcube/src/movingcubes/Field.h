/*
 * CubesField.h
 *
 *  Created on: Nov 14, 2012
 *      Author: imizus
 */


#ifndef CUBESFIELD_H_
#define CUBESFIELD_H_

#include <list>

#include "Shape.h"

using namespace std;

namespace sfmlcubes
{
	namespace movingcubes
	{
		class Field : public sf::NonCopyable
		{
		private:
			list<Shape*> cubesGroups;
			int width, height;

		public:
			Field(int width, int height): width(width), height(height) {}
			virtual ~Field() {}

			void advanceStep(double delta);
			bool anyTransitionsInProgress();

			list<Shape*>& getCubesGroups() { return cubesGroups; }

			list<Cube*> cubeAt(int i, int j);

			int getWidth() const { return width; }
			int getHeight() const { return height; }

			void glDraw(int dx, int dy);
		};
	}
}

#endif
