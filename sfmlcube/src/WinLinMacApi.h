/*
 * resourcelocator.h
 *
 *  Created on: 02.12.2012
 *      Author: Ilya Mizus
 */

#include <string>

#include <CoreFoundation/CFBundle.h>

using namespace std;

#ifndef RESOURCELOCATOR_H_
#define RESOURCELOCATOR_H_

class WinLinMacApi
{
public:
	string locateResource(const string& path, const string& filename);
};

#endif /* RESOURCELOCATOR_H_ */
