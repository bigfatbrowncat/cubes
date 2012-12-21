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
		class AnimatedPopupText
		{
		public:
			enum Type
			{
				tScore, tLines
			};
			enum AnimationType
			{
				atBonusCounter, atTextMessage
			};
		private:
			string text;
			int value;
			Type type;
			AnimationType animationType;
			Shape shape;
		public:
			AnimatedPopupText(string text, int value, Type type, AnimationType animationType, const Shape& shape);

			string getText() const { return text; }
			int getValue() const { return value; }
			Type getType() const { return type; }
			AnimationType getAnimationType() const { return animationType; }
			const Shape& getShape() const { return shape; }

			virtual ~AnimatedPopupText();
		};

	}
}
#endif
