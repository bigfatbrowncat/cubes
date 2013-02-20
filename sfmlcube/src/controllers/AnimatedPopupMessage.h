#ifndef ANIMATEDPOPUPMESSAGE_H_
#define ANIMATEDPOPUPMESSAGE_H_

#include "../movingcubes/ShapeState.h"
#include "AnimatedPopupLine.h"

namespace sfmlcubes
{
	using namespace movingcubes;

	namespace controllers
	{
		class AnimatedPopupMessage
		{
		private:
			ShapeState shapeState;
			list<AnimatedPopupLine> lines;
		public:
			AnimatedPopupMessage(const ShapeState& shapeState);

			AnimatedPopupMessage(const AnimatedPopupMessage& other) :
					shapeState(other.shapeState),
					lines(other.lines)
			{
				for (list<AnimatedPopupLine>::iterator iter = lines.begin(); iter != lines.end(); iter++)
				{
					(*iter).message = this;
				}
			}

			void addLine(const AnimatedPopupLine& newLine)
			{
				lines.push_back(newLine);
				lines.back().message = this;
			}

			int getLinesCount() const { return lines.size(); }
			ShapeState getShapeState() const { return shapeState; }
			const list<AnimatedPopupLine>::const_iterator getLinesBegin() const { return lines.begin(); }
			const list<AnimatedPopupLine>::const_iterator getLinesEnd() const { return lines.end(); }

			virtual ~AnimatedPopupMessage();
		};

	}
}

#endif
