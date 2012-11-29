/*
 * FallenController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLENCONTROLLER_H_
#define FALLENCONTROLLER_H_

#include "movingcubes/ShapeContainer.h"
#include "movingcubes/Shape.h"
#include "movingcubes/ShapeKinematics.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{
	class FallenController : public ShapeContainer
	{
		static float FALLING_DOWN_FIRED_LONGITUDE;
		static float BLINKING_LONGITUDE;

	public:
		enum State
		{
			sPassive,
			sBlinkingFullLines,
			sFiringFullLines
		};
	private:
		State state;

		int top, left, right, bottom;
		int linesFired;
		Shape fallen;

		list<Shape*> fallenNotFiredParts;
		map<ShapeKinematics*, int> firingLineCounts;
		list<ShapeKinematics*> fallenNotFiredPartKinematics;

		ShapeKinematics fallenKinematics;

		void collectLinesToFire();
		void removeFiredAwayLines();
		bool anyFiringTransitionsInProgress();
		void firingGroupsToFallen();

	public:
		FallenController(int top, int bottom, int left, int right);

		const Shape& getShape() const { return fallen; }
		list<Shape> getShapes() const
		{
			list<Shape> res;
			res.push_back(fallen);
			for (list<Shape*>::const_iterator iter = fallenNotFiredParts.begin();
			     iter != fallenNotFiredParts.end();
			     iter++)
			{
				res.push_back(**iter);
			}
			return res;
		}
		void setShape(const Shape& shape) { fallen = shape; }

		void processTimeStep(float dt);
		bool anyCollisions(const Shape& shape);

		void mergeShape(const Shape& other) { fallen += other; }
		void fireFullLines() { collectLinesToFire(); }
		int getLinesFired() const { return linesFired; }

		State getState() const { return state; }

		virtual ~FallenController();
	};
}
#endif
