/*
 * Cloneable.h
 *
 *  Created on: Feb 19, 2013
 *      Author: imizus
 */

#ifndef CLONEABLE_H_
#define CLONEABLE_H_

namespace sfmlcubes
{
	class Cloneable
	{
	public:
		// Every inherited class MyClass should
		// implement this method the same way:
		//
		// Cloneable* clone()
		// {
		//     return new MyClass(*this);
		// }
		//
		// assuming the copy constructor for MyClass is
		// correctly defined

		virtual Cloneable* clone() const = 0;
	};
}
#endif
