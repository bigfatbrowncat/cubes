/*
 * ClassicGameController.cpp
 *
 *  Created on: Dec 6, 2012
 *      Author: imizus
 */

#include "ClassicGameController.h"

namespace sfmlcubes
{
	namespace controllers
	{
		ClassicGameController::ClassicGameController() :
				board(12, 21, 24),

				rightKeyPressed(false),
				leftKeyPressed(false),
				downKeyPressed(false),
				rotateCWKeyPressed(false)
		{

		}

		void ClassicGameController::processTimeStep(float dt)
		{
			board.processTimeStep(dt);
		}

		void ClassicGameController::handleKeyPressed(sf::Event::KeyEvent key)
		{
	    	switch (key.code)
	    	{
	    	case sf::Keyboard::Right:
	    		if (!rightKeyPressed)
	    		{
	    			rightKeyPressed = true;
	    			board.turnOn(cmcMoveRight);
	    		}
	    		break;
	    	case sf::Keyboard::Left:
	    		if (!leftKeyPressed)
	    		{
	    			leftKeyPressed = true;
	        		board.turnOn(cmcMoveLeft);
	    		}
	    		break;
	    	case sf::Keyboard::Down:
	    		if (!downKeyPressed)
	    		{
	    			downKeyPressed = true;
	        		board.turnOn(cmcMoveDownFast);
	    		}
	    		break;
	    	case sf::Keyboard::Up:
	    		if (!rotateCWKeyPressed)
	    		{
	    			rotateCWKeyPressed = true;
	        		board.turnOn(cmcRotateCW);
	    		}
	    		break;
	    	case sf::Keyboard::Space:
	    		if (!board.isPaused())
	    		{
	    			board.turnOn(cmcPause);
	    		}
	    		else
	    		{
	    			board.turnOff(cmcPause);
	    		}
	    		break;
	    	default:
	    		break;
	    	}
		}

		void ClassicGameController::handleKeyReleased(sf::Event::KeyEvent key)
		{
	    	switch (key.code)
	    	{
	    	case sf::Keyboard::Right:
	    		rightKeyPressed = false;
	    		board.turnOff(cmcMoveRight);
	    		if (leftKeyPressed)
	    		{
	    			board.turnOn(cmcMoveLeft);
	    		}
	    		break;
	    	case sf::Keyboard::Left:
	    		leftKeyPressed = false;
	    		board.turnOff(cmcMoveLeft);
	    		if (rightKeyPressed)
	    		{
	    			board.turnOn(cmcMoveRight);
	    		}
	    		break;
	    	case sf::Keyboard::Down:
	    		downKeyPressed = false;
	    		board.turnOff(cmcMoveDownFast);
	    		break;
	    	case sf::Keyboard::Up:
	    		rotateCWKeyPressed = false;
	    		board.turnOff(cmcRotateCW);
	    		break;
	    	default:
	    		break;
	    	}
		}

		void ClassicGameController::handleFocusLost()
		{
			rightKeyPressed = false;
			leftKeyPressed = false;
			downKeyPressed = false;
			rotateCWKeyPressed = false;

			board.turnOff(cmcMoveRight);
			board.turnOff(cmcMoveLeft);
			board.turnOff(cmcMoveDownFast);
			board.turnOff(cmcRotateCW);

			board.turnOn(cmcPause);
		}


		ClassicGameController::~ClassicGameController()
		{
		}
	}
}
