/*
 * AnimatedPopupText.h
 *
 *  Created on: 09.12.2012
 *      Author: IL
 */

#ifndef ANIMATEDPOPUPTEXT_H_
#define ANIMATEDPOPUPTEXT_H_

#include <string>

#include <SFML/Graphics.hpp>
#include "../movingcubes/Shape.h"

using namespace std;

namespace sfmlcubes
{
	using namespace movingcubes;
	namespace controllers
	{
		class AnimatedPopupMessage;

		class AnimatedPopupLine
		{
			friend class AnimatedPopupMessage;
		public:
			enum ResourceType
			{
				tScore, tLines
			};
			enum AnimationType
			{
				atCounter, atMessage
			};
		private:
			string text;
			int value;
			ResourceType type;
			AnimationType animationType;
			AnimatedPopupMessage* message;
		public:
			AnimatedPopupLine(string text, int value, ResourceType type, AnimationType animationType);

			string getText() const
			{
				return text;
			}
			int getValue() const { return value; }
			ResourceType getType() const { return type; }
			AnimationType getAnimationType() const { return animationType; }
			const AnimatedPopupMessage& getMessage() const
			{
				return *message;
			}

			virtual ~AnimatedPopupLine();
		};

	}
}
#endif
