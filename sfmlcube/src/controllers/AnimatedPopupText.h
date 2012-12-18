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
			string text;
			Shape shape;
		public:
			AnimatedPopupText(string text, const Shape& shape);

			string getText() const { return text; }
			const Shape& getShape() const { return shape; }

			virtual ~AnimatedPopupText();
		};

	}
}
#endif
