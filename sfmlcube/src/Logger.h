/*
 * Logger.h
 *
 *  Created on: 16.11.2012
 *      Author: IL
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

using namespace std;

namespace sfmlcubes
{
	class Logger
	{
		Logger();
	public:
		void logError(const string& message) const;
		void logWarning(const string& message) const;
		void logInfo(const string& message) const;

		virtual ~Logger();

		static const Logger DEFAULT;
	};

}

#endif /* LOGGER_H_ */
