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
	const Logger Logger::DEFAULT;

	Logger::Logger()
	{
		// TODO Auto-generated constructor stub
	}

	Logger::~Logger()
	{
		// TODO Auto-generated destructor stub
	}

	void Logger::logError(const string& message) const
	{
		printf("[LOG] Error: %s\n", message.c_str());
		fflush(stdout);
	}

	void Logger::logWarning(const string& message) const
	{
		printf("[LOG] Warning: %s\n", message.c_str());
		fflush(stdout);
	}

	void Logger::logInfo(const string& message) const
	{
		printf("[LOG] Info: %s\n", message.c_str());
		fflush(stdout);
	}
}
