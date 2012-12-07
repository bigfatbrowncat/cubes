/*
 * resourcelocator.h
 *
 *  Created on: 02.12.2012
 *      Author: Ilya Mizus
 */

#include <string>

#include <SFML/Window.hpp>

using namespace std;

#ifndef RESOURCELOCATOR_H_
#define RESOURCELOCATOR_H_

class WinLinMacApi
{
public:
	string locateResource(const string& path, const string& filename);
	void setMainWindowIcon(const sf::Window& win);
};

#endif /* RESOURCELOCATOR_H_ */
