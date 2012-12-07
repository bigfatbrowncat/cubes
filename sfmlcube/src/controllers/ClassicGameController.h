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
			CubesField board;//(12, 21);

			bool rightKeyPressed, leftKeyPressed, downKeyPressed, rotateCWKeyPressed;

		public:
			ClassicGameController();
			void processTimeStep(float dt);
			void handleKeyPressed(sf::Event::KeyEvent key);
			void handleKeyReleased(sf::Event::KeyEvent key);
			void handleFocusLost();

			const CubesField& getCubesField() const { return board; }

			virtual ~ClassicGameController();
		};
	}
}
#endif
