/*
 * resourcelocator.h
 *
 *  Created on: 02.12.2012
 *      Author: svp
 */

#ifndef RESOURCELOCATOR_H_
#define RESOURCELOCATOR_H_

bool initializeBundle();
void finalizeBundle();

char* locateResource(const char* path, const char* filename);


#endif /* RESOURCELOCATOR_H_ */
