/*
 * ErrorHandling.c
 *
 *  Created on: Nov 12, 2024
 *      Author: Ethan
 */

#include <ErrorHandling.h>

void APPLICATION_ASSERT(bool in)
{
	if(in)
		for(;;);
}
