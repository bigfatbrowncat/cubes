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
			float age;
		public:
			AnimatedPopupText(string text);

			string getText() const { return text; }
			float getAge() { return age; }

			void processTimeStep(float dt) { age += dt; }

			bool operator == (const AnimatedPopupText& other)
			{
				return other.uId == uId;
			}

			virtual ~AnimatedPopupText();
		};

	}
}
#endif
