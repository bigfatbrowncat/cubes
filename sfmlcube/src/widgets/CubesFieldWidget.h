/*
 * CubesFieldWidget.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CUBESFIELDWIDGET_H_
#define CUBESFIELDWIDGET_H_

#include "../controllers/CubesField.h"

namespace sfmlcubes
{
	using namespace controllers;
	namespace widgets
	{
		class CubesFieldWidget
		{
		private:
			const CubesField& cubesField;

			void setPerspective();
		public:
			CubesFieldWidget(const CubesField& cubesField);
			void drawBoard();
			virtual ~CubesFieldWidget();
		};
	}
}
#endif
