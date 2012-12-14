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
		private:
			static int lastUId;
		private:
			string text;
			Shape shape;
			int uId;
		public:
			AnimatedPopupText(string text, const Shape& shape);

			string getText() const { return text; }
			const Shape& getShape() const { return shape; }

			bool operator == (const AnimatedPopupText& other) const
			{
				return other.uId == uId;
			}
			bool operator < (const AnimatedPopupText& other) const
			{
				return other.uId < uId;
			}

			virtual ~AnimatedPopupText();
		};

	}
}
#endif
