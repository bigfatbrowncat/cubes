/*
 * RowWithKinematics.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: imizus
 */

#include "FallenRow.h"
#include "../Logger.h"

namespace sfmlcubes
{
	namespace controllers
	{
		FallenRow::FallenRow(TimingManager& timingManager, const VelocityController& velocityController, const ShapeCubes& source, int left, int right, int j) :
				FallenPart(timingManager, velocityController),
				left(left),
				right(right),
				j(j),
				type(tUnknown)
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
			shape.setCubes(lineCubes);
		}

		FallenRow* FallenRow::fromDealer(TimingManager& timingManager, const VelocityController& velocityController, BackgroundDealer& backgroundDealer, int left, int right, int j)
		{
			ShapeCubes shp;
			backgroundDealer.setWidth(right - left + 1);
			vector<BackgroundDealer::CellType> newRow = backgroundDealer.dealRow();
			for (size_t i = 0; i < newRow.size(); i++)
			{
				switch (newRow[i])
				{
				case BackgroundDealer::ctEmpty:
					// add nothing
					break;
				case BackgroundDealer::ctWall:
					// add wall
					shp.addCube(Cube(i + left, j, Cube::mtWall, sf::Color(128, 128, 128)));
					break;
				default:
					Logger::DEFAULT.logWarning("Strange case here...");
					break;
				}
			}
			return new FallenRow(timingManager, velocityController, shp, left, right, j);
		}


		bool FallenRow::lineIsFull()
		{
			for (int i = left; i <= right; i++)
			{
				if (shape.getCubes().cubeAt(i, j).empty()) return false;
			}
			return true;
		}
	}

}
