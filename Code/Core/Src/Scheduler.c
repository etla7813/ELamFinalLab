/*
 * Scheduler.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Ethan
 */
#include <Scheduler.h>

static uint32_t scheduledEvents;

void addSchedulerEvent(uint32_t event)
{
	scheduledEvents |= event; //sets event bit to 1 (add)
}
void removeSchedulerEvent(uint32_t event)
{
	scheduledEvents &= ~event; //sets event bit to 0 (erase)
}

uint32_t getScheduledEvents()
{
	return scheduledEvents;
}


