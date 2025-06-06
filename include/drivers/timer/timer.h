/*
 * timer.h
 * ---
 * Interface for ARM Generic Timer
 * ---
 * Daniel Yun
 */

#ifndef __TIMER_H__
#define __TIMER_H__


void timer_init(void);
void timer_reset(void);
void timer_handler(void);


#endif // __TIMER_H__
