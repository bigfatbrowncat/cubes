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
	class ConsoleLogger;
	class FileLogger;

	class Logger
	{
	public:
		virtual void logError(const string& message) const = 0;
		virtual void logWarning(const string& message) const = 0;
		virtual void logInfo(const string& message) const = 0;
		virtual ~Logger() {}

		static const FileLogger DEFAULT;
	};

	class ConsoleLogger
	{
	public:
		ConsoleLogger();
		virtual void logError(const string& message) const;
		virtual void logWarning(const string& message) const;
		virtual void logInfo(const string& message) const;

		virtual ~ConsoleLogger();

	};

	class FileLogger
	{
		FILE* logFile;
	public:
		FileLogger();
		virtual void logError(const string& message) const;
		virtual void logWarning(const string& message) const;
		virtual void logInfo(const string& message) const;

		virtual ~FileLogger();

	};
}

#endif /* LOGGER_H_ */
