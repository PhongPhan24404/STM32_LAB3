/*
 * software_timer.h
 *
 *  Created on: Nov 20, 2024
 *      Author: phong
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int TICK;

extern int timer_flag1;
extern int timer_counter1;

extern int timer_flag2;
extern int timer_counter2;

extern int timer_flag3;
extern int timer_counter3;

extern int timer_flag4;
extern int timer_counter4;

extern int timer_flag5;
extern int timer_counter5;

extern int timer_flag6;
extern int timer_counter6;

extern int timer_flag7;
extern int timer_counter7;

extern int timer_flag8;
extern int timer_counter8;

extern int timer_flag9;
extern int timer_counter9;

extern int timer_flag10;
extern int timer_counter10;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void setTimer4(int duration);
void setTimer5(int duration);
void setTimer6(int duration);
void setTimer7(int duration);
void setTimer8(int duration);
void setTimer9(int duration);
void setTimer10(int duration);


void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
