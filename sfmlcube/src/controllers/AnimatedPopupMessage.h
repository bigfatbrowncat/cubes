#ifndef ANIMATEDPOPUPMESSAGE_H_
#define ANIMATEDPOPUPMESSAGE_H_

#include "../movingcubes/Shape.h"
#include "AnimatedPopupLine.h"

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		class AnimatedPopupMessage
		{
		private:
			ShapeCubes shape;
			list<AnimatedPopupLine> lines;
		public:
			AnimatedPopupMessage(const ShapeCubes& shape);

			AnimatedPopupMessage(const AnimatedPopupMessage& other)
			{
				*this = other;
			}

			const AnimatedPopupMessage& operator = (const AnimatedPopupMessage& other)
			{
				shape = other.shape;
				lines = other.lines;

				for (list<AnimatedPopupLine>::iterator iter = lines.begin(); iter != lines.end(); iter++)
				{
					(*iter).message = this;
				}
				return *this;
			}

			void addLine(const AnimatedPopupLine& newLine)
			{
				lines.push_back(newLine);
				lines.back().message = this;
			}

			int getLinesCount() const { return lines.size(); }
			ShapeCubes getShapeCubes() const { return shape; }
			const list<AnimatedPopupLine>::const_iterator getLinesBegin() const { return lines.begin(); }
			const list<AnimatedPopupLine>::const_iterator getLinesEnd() const { return lines.end(); }

			virtual ~AnimatedPopupMessage();
		};

	}
}

#endif
