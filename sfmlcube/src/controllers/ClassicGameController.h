/*
 * ClassicGameController.h
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#ifndef CLASSICGAMECONTROLLER_H_
#define CLASSICGAMECONTROLLER_H_

#include <SFML/Window.hpp>

#include "CubesField.h"

namespace sfmlcubes
{
	namespace controllers
	{
		class ClassicGameController
		{
		private:
			TimingManager timingManager;
			CubesField board;//(12, 21);

			bool rightKeyPressed, leftKeyPressed, downKeyPressed, rotateCWKeyPressed;

		public:
			ClassicGameController();
			void handleKeyPressed(sf::Event::KeyEvent key);
			void handleKeyReleased(sf::Event::KeyEvent key);
			void handleFocusLost();

			void processTimeStep(double dt) { timingManager.processTimeStep(dt); }

			const CubesField& getCubesField() const { return board; }

			virtual ~ClassicGameController();
		};
	}
}
#endif
