/*
 * RowWithKinematics.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "RowWithKinematics.h"

namespace sfmlcubes
{
	namespace controllers
	{

		float RowWithKinematics::BLINKING_LONGITUDE = 0.6;

		RowWithKinematics::RowWithKinematics(TimingManager& timingManager, const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j) :
				line(timingManager),
				velocityController(velocityController),
				kinematics(timingManager, line),
				left(left),
				right(right),
				j(j),
				blink(false),
				moveBy(0)
		{
			ShapeCubes lineCubes;
			for (int i = left; i <= right; i++)
			{
				if (!source.cubeAt(i, j).empty())
				{
					// Adding the cube to the current firing group
					if (source.cubeAt(i, j).size() > 1) Logger::DEFAULT.logWarning("cubeAt returned more than one cube");
					lineCubes.addCube(source.cubeAt(i, j).back());
				}
			}
			line.setCubes(lineCubes);
		}

		bool RowWithKinematics::lineIsFull()
		{
			for (int i = left; i <= right; i++)
			{
				if (line.getCubes().cubeAt(i, j).empty()) return false;
			}
			return true;
		}

		bool RowWithKinematics::lineIsEmpty()
		{
			for (int i = left; i <= right; i++)
			{
				if (!line.getCubes().cubeAt(i, j).empty()) return false;
			}
			return true;
		}

	}

}
