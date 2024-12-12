/*
 * Scheduler.h
 *
 *  Created on: Sep 12, 2024
 *      Author: Ethan
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include <stdint.h>

//#define LED_TOGGLE_EVENT	(1 << 0)
//#define LED_DELAY_EVENT		(1 << 1)
//#define POLL_EVENT			(1 << 2)

//lab5 additions and the ones previous not needed
#define START_GAME (1 << 0)

uint32_t 	getScheduledEvents();
void 		addSchedulerEvent(uint32_t event);
void	 	removeSchedulerEvent(uint32_t event);


#endif /* SCHEDULER_H_ */
