/*
 * BackgroundDealer.h
 *
 *  Created on: Feb 13, 2013
 *      Author: imizus
 */

#ifndef BACKGROUNDDEALER_H_
#define BACKGROUNDDEALER_H_

#include <stdlib.h>
#include <vector>

using namespace std;

namespace sfmlcubes
{
	namespace controllers
	{
		class BackgroundDealer
		{
		public:
			enum CellType
			{
				ctEmpty,
				ctWall
			};

		private:
			int width;
			vector<CellType> lastRow;
			int randomValue;

			int nextRandom()
			{
				randomValue = randomValue * 1103515245 + 12345;
				return (randomValue % ((unsigned int)RAND_MAX + 1));
			}

		public:
			BackgroundDealer(int width);
			virtual ~BackgroundDealer();

			void setWidth(int value)
			{
				if (width != value)
				{
					width = value;
				}
			}

			int getWidth() { return width; }

			vector<CellType> dealRow()
			{
				vector<CellType> res(width, ctEmpty);
				for (int i = 0; i < width; i++)
				{
					res[i] = (nextRandom() < RAND_MAX / 50) ? ctWall : ctEmpty;
				}
				return res;
			}
		};

	}
}
#endif
