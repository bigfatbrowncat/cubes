/*
 * FallenRows.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: imizus
 */

#include "FallenRows.h"

namespace sfmlcubes
{
	namespace controllers
	{
		FallenRows::FallenRows(TimingManager& timingManager) :
			timingManager(timingManager)
		{
		}

		void FallenRows::give(FallenRow* row)
		{
			lines.push_back(row);
		}

		FallenRow* FallenRows::editableRowAt(int j)
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getJ() == j)
			    {
			    	return (*iter);
			    }
			}
			return NULL;
		}
		const FallenRow* FallenRows::getRowAt(int j) const
		{
			for (list<FallenRow*>::const_iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getJ() == j)
			    {
			    	return (*iter);
			    }
			}
			return NULL;
		}

		FallenRows::~FallenRows()
		{
		}

		void FallenRows::startFalling()
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tFallingDown ||
				    (*iter)->getType() == FallenRow::tRemaining)
			    {
			    	(*iter)->startAnimation();
			    }
			}
		}

		void FallenRows::startBlinking()
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tBurning)
			    {
			    	(*iter)->startAnimation();
			    }
			}
		}

		bool FallenRows::isBurningBlinkingInProgress()
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tBurning)
			    {
					if ((*iter)->isBlinkingInProgress()) return true;
			    }
			}
			return false;
		}

		bool FallenRows::isFallingInProgress()
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tFallingDown ||
				    (*iter)->getType() == FallenRow::tRemaining)
			    {
					if ((*iter)->isMovingInProgress()) return true;
			    }
			}
			return false;
		}

		void FallenRows::addAllRemainingToShapeDynamics(ShapeDynamics& shapeDynamics)
		{
			for (list<FallenRow*>::const_iterator iter = lines.begin();
				 iter != lines.end();
				 iter ++)
			{
				if ((*iter)->getType() == FallenRow::tRemaining)
				{
					shapeDynamics.addObstacle((*iter)->getShape());
				}
			}
		}

		void FallenRows::setFallByForFallingDown(int fallBy)
		{
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tFallingDown)
				{
					(*iter)->setFallBy(fallBy);
				}
			}
		}

		ShapeCubes FallenRows::toShapeCubes()
		{
			ShapeCubes res;
			for (list<FallenRow*>::const_iterator iter = lines.begin();
				 iter != lines.end();
				 iter++)
			{
				res += (*iter)->getShape().getCubes();
			}
			return res;
		}

		void FallenRows::toShapes(list<const Shape*>& shapes) const
		{
			for (list<FallenRow*>::const_iterator iter = lines.begin();
				 iter != lines.end();
				 iter++)
			{
				shapes.push_back(&((*iter)->getShape()));
			}
		}


		int FallenRows::countBurningLines()
		{
			int res = 0;
			for (list<FallenRow*>::iterator iter = lines.begin(); iter != lines.end(); iter++)
			{
				if ((*iter)->getType() == FallenRow::tBurning)
				{
					res++;
				}
			}
			return res;
		}

		void FallenRows::removeBurningLines()
		{
			list<FallenRow*>::iterator iter = lines.begin();
			while (iter != lines.end())
			{
				if ((*iter)->getType() == FallenRow::tBurning)
				{
					FallenRow* toRemove = *iter;
					iter = lines.erase(iter);
					delete toRemove;
				}
				else
				{
					iter ++;
				}
			}

		}

		void FallenRows::clear()
		{
			list<FallenRow*>::iterator iter = lines.begin();
			while (iter != lines.end())
			{
				FallenRow* toRemove = *iter;
				iter = lines.erase(iter);
				delete toRemove;
			}
		}

	}
}
