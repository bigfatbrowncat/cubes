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

using namespace std;

namespace sfmlcubes
{
	namespace controllers
	{
		class AnimatedPopupText
		{
		private:
			static int lastUId;
		private:
			string text;
			int uId;
		public:
			AnimatedPopupText(string text);

			string getText() const { return text; }

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
