/*
 * software_timer.c
 *
 *  Created on: Nov 20, 2024
 *      Author: phong
 */
#include "Software_timer.h"

int TICK = 10;

int timer_flag1 = 0;
int timer_counter1 = 0;

int timer_flag2 = 0;
int timer_counter2 = 0;

int timer_flag3 = 0;
int timer_counter3 = 0;

int timer_flag4 = 0;
int timer_counter4 = 0;

int timer_flag5 = 0;
int timer_counter5 = 0;

int timer_flag6 = 0;
int timer_counter6 = 0;

int timer_flag7 = 0;
int timer_counter7 = 0;

int timer_flag8 = 0;
int timer_counter8 = 0;

int timer_flag9 = 0;
int timer_counter9 = 0;

int timer_flag10 = 0;
int timer_counter10 = 0;

void setTimer1(int duration){
	timer_flag1 = 0;
	timer_counter1 = duration / TICK;
}

void setTimer2(int duration){
	timer_flag2 = 0;
	timer_counter2 = duration / TICK;
}

void setTimer3(int duration){
	timer_flag3 = 0;
	timer_counter3 = duration / TICK;
}

void setTimer4(int duration){
	timer_flag4 = 0;
	timer_counter4 = duration / TICK;
}

void setTimer5(int duration){
	timer_flag5 = 0;
	timer_counter5 = duration / TICK;
}

void setTimer6(int duration){
	timer_flag6 = 0;
	timer_counter6 = duration / TICK;
}

void setTimer7(int duration){
	timer_flag7 = 0;
	timer_counter7 = duration / TICK;
}

void setTimer8(int duration){
	timer_flag8 = 0;
	timer_counter8 = duration / TICK;
}

void setTimer9(int duration){
	timer_flag9 = 0;
	timer_counter9 = duration / TICK;
}

void setTimer10(int duration){
	timer_flag10 = 0;
	timer_counter10 = duration / TICK;
}

void timerRun(){
		if(timer_counter1 > 0){
			timer_counter1--;
		if(timer_counter1 <= 0){
			timer_flag1 = 1;
			}
		}

		if(timer_counter2 > 0){
			timer_counter2--;
		if(timer_counter2 <= 0){
			timer_flag2 = 1;
			}
		}

		if(timer_counter3 > 0){
			timer_counter3--;
		if(timer_counter3 <= 0){
			timer_flag3 = 1;
			}
		}

		if(timer_counter4 > 0){
			timer_counter4--;
		if(timer_counter4 <= 0){
			timer_flag4 = 1;
			}
		}

		if(timer_counter5 > 0){
			timer_counter5--;
		if(timer_counter5 <= 0){
			timer_flag5 = 1;
			}
		}

		if(timer_counter6 > 0){
			timer_counter6--;
		if(timer_counter6 <= 0){
			timer_flag6 = 1;
			}
		}

		if(timer_counter7 > 0){
			timer_counter7--;
		if(timer_counter7 <= 0){
			timer_flag7 = 1;
			}
		}

		if(timer_counter8 > 0){
			timer_counter8--;
		if(timer_counter8 <= 0){
			timer_flag8 = 1;
			}
		}

		if(timer_counter9 > 0){
			timer_counter9--;
		if(timer_counter9 <= 0){
			timer_flag9 = 1;
			}
		}

		if(timer_counter10 > 0){
			timer_counter10--;
		if(timer_counter10 <= 0){
			timer_flag10 = 1;
			}
		}
}

