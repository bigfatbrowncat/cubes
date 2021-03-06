/*
 * Logger.cpp
 *
 *  Created on: 16.11.2012
 *      Author: IL
 */

#include <cstdio>

#include "Logger.h"

using namespace std;

namespace sfmlcubes
{
#ifdef DEBUG
	const ConsoleLogger Logger::DEFAULT;
#else
	const ConsoleLogger Logger::DEFAULT;
#endif

	ConsoleLogger::ConsoleLogger()
	{
		// TODO Auto-generated constructor stub
	}

	ConsoleLogger::~ConsoleLogger()
	{
		// TODO Auto-generated destructor stub
	}

	void ConsoleLogger::logError(const string& message) const
	{
		fprintf(stderr, "[LOG] Error: %s\n", message.c_str());
		fflush(stdout);
		fflush(stderr);
	}

	void ConsoleLogger::logWarning(const string& message) const
	{
		printf("[LOG] Warning: %s\n", message.c_str());
		fflush(stdout);
		fflush(stderr);
	}

	void ConsoleLogger::logInfo(const string& message) const
	{
		printf("[LOG] Info: %s\n", message.c_str());
		fflush(stdout);
		fflush(stderr);
	}



	FileLogger::FileLogger()
	{
		logFile = fopen("cubes.log", "w");
	}

	FileLogger::~FileLogger()
	{
		fclose(logFile);
	}

	void FileLogger::logError(const string& message) const
	{
		fprintf(logFile, "[LOG] Error: %s\n", message.c_str());
	}

	void FileLogger::logWarning(const string& message) const
	{
		fprintf(logFile, "[LOG] Warning: %s\n", message.c_str());
	}

	void FileLogger::logInfo(const string& message) const
	{
		fprintf(logFile, "[LOG] Info: %s\n", message.c_str());
	}
}
