/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "button.h"
#include "software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define AUTOLIGHT		1
#define RED_CHANGE		2
#define YELLOW_CHANGE	3
#define GREEN_CHANGE	4
#define RED_GREEN	6
#define RED_YELLOW	7
#define GREEN_RED	8
#define YELLOW_RED	9


#define MOD_INIT	10


extern int mode;
extern int status;
extern int status_system;
extern int num;

extern int indexBuffer;
extern int led_buffer[];

extern int TIME_RED;
extern int TIME_YELLOW;
extern int TIME_GREEN;

extern int TIME_RED_tmp;
extern int TIME_YELLOW_tmp;
extern int TIME_GREEN_tmp;


//begin default
int status = MOD_INIT;
int status_system = 0;
int mode = AUTOLIGHT;
int num = 0;


int TIME_RED = 5;
int TIME_YELLOW = 2;
int TIME_GREEN = 3;

int TIME_RED_tmp = 0;
int TIME_YELLOW_tmp = 0;
int TIME_GREEN_tmp = 0;

int indexBuffer = 0;
int led_buffer[6] = {};


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// light setup:

void toggleAllRed(){
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(GPIOA, REDA);
	HAL_GPIO_TogglePin(GPIOA, REDB);
}

void toggleAllGreen(){
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(GPIOA, GREENA);
	HAL_GPIO_TogglePin(GPIOA, GREENB);
}

void toggleAllYellow(){
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(GPIOA, YELLOWA);
	HAL_GPIO_TogglePin(GPIOA, YELLOWB);
}

void setRedAGreenB()
{
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_SET);
}

void setRedAYellowB()
{
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
}

void setGreenARedB()
{
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
}

void setYellowARedB()
{
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
}


void OffAllLed()
{
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
}

void offGreenYellow()
{
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
}

void offGreenRed()
{
	HAL_GPIO_WritePin(GPIOA, GREENB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GREENA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);
}

void offRedYellow()
{
	HAL_GPIO_WritePin(GPIOA, YELLOWB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, YELLOWA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, REDA, GPIO_PIN_RESET);
}

void display7SEG_horizontal(int num)
{
	switch(num){
	  case 0:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_SET);
		  break;
	  case 1:
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_SET);
		  break;
	  case 2:
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 3:
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 4:
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 5:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 6:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 7:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_SET);
		  break;
	  case 8:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;
	  case 9:
		  HAL_GPIO_WritePin(GPIOB, SEG1_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG1_6, GPIO_PIN_RESET);
		  break;

	}
}

void display7SEG_vertical(int num)
{
	switch(num){
	  case 0:
		  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_SET);
		  break;
	  case 1:
		  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_SET);
		  break;
	  case 2:
		  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 3:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 4:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 5:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 6:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 7:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_SET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_SET);
		  break;
	  case 8:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;
	  case 9:
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_0, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_1, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_2, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_3, GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOB, SEG2_4, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_5, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, SEG2_6, GPIO_PIN_RESET);
		  break;

	}
}

void update7SEG(int indexBuffer){
	switch(indexBuffer){
	case 0:
		HAL_GPIO_WritePin(GPIOA, EN0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN3, GPIO_PIN_SET);
		break;

	case 1:
		HAL_GPIO_WritePin(GPIOA, EN0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, EN2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3, GPIO_PIN_RESET);
		break;

	default:
		break;
	}
}

/**
 * @brief Cập nhật buffer hiển thị LED 7 đoạn.
 * Hàm  chia thời gian thành các phần hàng chục và đơn vị rồi lưu vào mảng `led_buffer`.
 */
void updateBuffer()
{
    led_buffer[0] = TIME_RED / 10;
    led_buffer[1] = TIME_RED % 10;
    led_buffer[2] = TIME_GREEN / 10;
    led_buffer[3] = TIME_GREEN % 10;
    led_buffer[4] = TIME_YELLOW / 10;
    led_buffer[5] = TIME_YELLOW % 10;
}

/**
 * @brief Thực hiện đếm ngược cho các giá trị trong `led_buffer`.
 * Hàm  xử lý đếm ngược cho từng cặp giá trị (hàng chục và đơn vị)
 * và đặt lại thời gian khi giá trị đếm ngược về 0.
 */
void countdown7SEG() {
    int i;
    for (i = 0; i < 6; i += 2) {
        if (led_buffer[i + 1] < 0 && led_buffer[i] > 0) {
            led_buffer[i + 1] = 9;
            led_buffer[i]--;
        }
        if (led_buffer[i] == 0 && led_buffer[i + 1] == 0) {
            if (i == 0) { // Đèn đỏ
                led_buffer[0] = TIME_RED / 10;
                led_buffer[1] = TIME_RED % 10;
            } else if (i == 2) { // Đèn xanh
                led_buffer[2] = TIME_GREEN / 10;
                led_buffer[3] = TIME_GREEN % 10;
            } else if (i == 4) { // Đèn vàng
                led_buffer[4] = TIME_YELLOW / 10;
                led_buffer[5] = TIME_YELLOW % 10;
            }
        }
    }
}

/**
 * @brief Điều khiển hiển thị và logic đèn đỏ, vàng (hệ thống 7 đoạn).
 * Hàm  thực hiện việc đếm ngược và cập nhật hiển thị cho đèn đỏ và vàng
 * trong hệ thống đèn 7 đoạn dựa trên trạng thái hệ thống.
 */
void led7SEG_YR() {
    switch (status_system) {
        case 0:
            countdown7SEG();
            setTimer1(500);
            status_system = 1;
            break;
        case 1:
            update7SEG(0);
            display7SEG_horizontal(led_buffer[4]); // Hàng chục đèn vàng
            display7SEG_vertical(led_buffer[0]); // Hàng chục đèn đỏ
            if (timer_flag1 == 1) {
                status_system = 2;
                setTimer1(500);
            }
            break;
        case 2:
            update7SEG(1);
            display7SEG_horizontal(led_buffer[5]); // Hàng đơn vị đèn vàng
            display7SEG_vertical(led_buffer[1]); // Hàng đơn vị đèn đỏ
            if (timer_flag1 == 1) {
                led_buffer[1]--;
                led_buffer[5]--;
                status_system = 0;
            }
            break;
    }
}


/**
 * @brief Điều khiển hiển thị và logic đèn đỏ, xanh (hệ thống 7 đoạn).
 * Hàm  thực hiện việc đếm ngược và cập nhật hiển thị cho đèn đỏ và xanh
 * trong hệ thống đèn 7 đoạn dựa trên trạng thái hệ thống.
 */
void led7SEG_GR() {
    switch (status_system) {
        case 0:
            countdown7SEG();
            setTimer1(500);
            status_system = 1;
            break;
        case 1:
            update7SEG(0);
            display7SEG_horizontal(led_buffer[2]); // Hàng chục đèn xanh
            display7SEG_vertical(led_buffer[0]); // Hàng chục đèn đỏ
            if (timer_flag1 == 1) {
                status_system = 2;
                setTimer1(500);
            }
            break;
        case 2:
            update7SEG(1);
            display7SEG_horizontal(led_buffer[3]); // Hàng đơn vị đèn xanh
            display7SEG_vertical(led_buffer[1]); // Hàng đơn vị đèn đỏ
            if (timer_flag1 == 1) {
                led_buffer[1]--; // Giảm đèn đỏ
                led_buffer[3]--; // Giảm đèn xanh
                status_system = 0;
            }
            break;
    }
}

/**
 * @brief Điều khiển hiển thị và logic đèn đỏ, vàng (hệ thống 7 đoạn).
 * Hàm  thực hiện việc đếm ngược và cập nhật hiển thị cho đèn đỏ và vàng
 * trong hệ thống đèn 7 đoạn dựa trên trạng thái hệ thống.
 */
void led7SEG_RY() {
    switch (status_system) {
        case 0:
            countdown7SEG();
            setTimer1(500);
            status_system = 1;
            break;
        case 1:
            update7SEG(0);
            display7SEG_horizontal(led_buffer[0]); // Hàng chục đèn đỏ
            display7SEG_vertical(led_buffer[4]); // Hàng chục đèn vàng
            if (timer_flag1 == 1) {
                status_system = 2;
                setTimer1(500);
            }
            break;
        case 2:
            update7SEG(1);
            display7SEG_horizontal(led_buffer[1]); // Hàng đơn vị đèn đỏ
            display7SEG_vertical(led_buffer[5]); // Hàng đơn vị đèn vàng
            if (timer_flag1 == 1) {
                led_buffer[1]--; // Giảm đèn đỏ
                led_buffer[5]--; // Giảm đèn vàng
                status_system = 0;
            }
            break;
    }
}

/**
 * @brief Điều khiển hiển thị và logic đèn đỏ, xanh (hệ thống 7 đoạn).
 * Hàm  thực hiện việc đếm ngược và cập nhật hiển thị cho đèn đỏ và xanh
 * trong hệ thống đèn 7 đoạn dựa trên trạng thái hệ thống.
 */
void led7SEG_RG() {
    switch (status_system) {
        case 0:
            countdown7SEG();
            setTimer1(500);
            status_system = 1;
            break;
        case 1:
            update7SEG(0);
            display7SEG_horizontal(led_buffer[0]); // Hàng chục đèn đỏ
            display7SEG_vertical(led_buffer[2]); // Hàng chục đèn xanh
            if (timer_flag1 == 1) {
                status_system = 2;
                setTimer1(500);
            }
            break;
        case 2:
            update7SEG(1);
            display7SEG_horizontal(led_buffer[1]); // Hàng đơn vị đèn đỏ
            display7SEG_vertical(led_buffer[3]); // Hàng đơn vị đèn xanh
            if (timer_flag1 == 1) {
                led_buffer[1]--; // Giảm đèn đỏ
                led_buffer[3]--; // Giảm đèn xanh
                status_system = 0;
            }
            break;
    }
}

/**
 * @brief Hiển thị LED 7 đoạn dựa trên trạng thái hiện tại.
 * Hàm  sẽ gọi các hàm tương ứng để điều khiển hiển thị đèn
 * theo các trạng thái khác nhau.
 */
void display7SEG(){
    switch(status){
        case RED_GREEN:
            led7SEG_RG();
            break;
        case RED_YELLOW:
            led7SEG_RY();
            break;
        case GREEN_RED:
            led7SEG_GR();
            break;
        case YELLOW_RED:
            led7SEG_YR();
            break;
        default:
            break;
    }
}

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/**
 * @brief Điều khiển trạng thái tự động của hệ thống.
 * Hàm  thực hiện việc chuyển đổi trạng thái hệ thống và điều khiển
 * thời gian cho các đèn dựa trên trạng thái hiện tại.
 */
void fsm_automatic()
{
    switch (status){
        case MOD_INIT:
            status = RED_GREEN; // Chuyển sang trạng thái đèn đỏ - xanh
            setTimer6(TIME_RED*1000); // Đặt thời gian cho đèn đỏ
            setTimer2(TIME_GREEN*1000); // Đặt thời gian cho đèn xanh
            break;
        case RED_GREEN:
            display7SEG(); // Hiển thị LED 7 đoạn cho trạng thái hiện tại
            setRedAGreenB(); // Thiết lập đèn đỏ và xanh
            if(timer_flag2 == 1){
                status = RED_YELLOW; // Chuyển sang trạng thái đèn đỏ - vàng
                setTimer6(TIME_RED*1000); // Đặt lại thời gian cho đèn đỏ
                setTimer2(TIME_YELLOW*1000); // Đặt thời gian cho đèn vàng
            }
            break;
        case RED_YELLOW:
            display7SEG(); // Hiển thị LED 7 đoạn cho trạng thái hiện tại
            setRedAYellowB(); // Thiết lập đèn đỏ và vàng
            if(timer_flag2 == 1){
                status = GREEN_RED; // Chuyển sang trạng thái đèn xanh - đỏ
                setTimer6(TIME_RED*1000); // Đặt lại thời gian cho đèn đỏ
                setTimer2(TIME_GREEN*1000); // Đặt lại thời gian cho đèn xanh
            }
            break;
        case GREEN_RED:
            display7SEG(); // Hiển thị LED 7 đoạn cho trạng thái hiện tại
            setGreenARedB(); // Thiết lập đèn xanh và đỏ
            if(timer_flag2 == 1){
                status = YELLOW_RED; // Chuyển sang trạng thái đèn vàng - đỏ
                setTimer6(TIME_RED*1000); // Đặt lại thời gian cho đèn đỏ
                setTimer2(TIME_YELLOW*1000); // Đặt lại thời gian cho đèn vàng
            }
            break;
        case YELLOW_RED:
            display7SEG(); // Hiển thị LED 7 đoạn cho trạng thái hiện tại
            setYellowARedB(); // Thiết lập đèn vàng và đỏ
            if(timer_flag2 == 1){
                status = RED_GREEN; // Chuyển sang trạng thái đèn đỏ - xanh
                setTimer6(TIME_RED*1000); // Đặt lại thời gian cho đèn đỏ
                setTimer2(TIME_GREEN*1000); // Đặt lại thời gian cho đèn xanh
            }
            break;
        default:
            break;
    }
}


/**
 * @brief Chuyển đổi chế độ hiển thị của hệ thống.
 * Hàm  cập nhật hiển thị cho hệ thống LED 7 đoạn dựa trên giá trị `temp`
 * và thực hiện các tác vụ dựa trên giá trị của `num`.
 *
 * @param temp Giá trị hiện tại của chế độ.
 */
void modifyMode(int temp){
    switch(num){
        case 0:
            num = 1; // Chuyển sang bước tiếp theo trong chế độ
            setTimer4(250); // Đặt thời gian cho bước tiếp theo
            break;
        case 1:
            update7SEG(0); // Cập nhật hiển thị LED 7 đoạn
            display7SEG_horizontal(mode/10); // Hiển thị giá trị hàng chục của chế độ
            display7SEG_vertical(temp/10); // Hiển thị giá trị hàng chục của thời gian
            if(timer_flag4 == 1){
                setTimer4(250); // Đặt thời gian cho bước tiếp theo
                num = 2; // Chuyển sang bước tiếp theo trong chế độ
            }
            break;
        case 2:
            update7SEG(1); // Cập nhật hiển thị LED 7 đoạn
            display7SEG_horizontal(mode%10); // Hiển thị giá trị hàng đơn vị của chế độ
            display7SEG_vertical(temp%10); // Hiển thị giá trị hàng đơn vị của thời gian
            if(timer_flag4 == 1){
                setTimer4(250); // Đặt thời gian cho bước tiếp theo
                num = 1; // Quay lại bước trước trong chế độ
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Điều khiển chế độ thủ công của hệ thống.
 * Hàm  thực hiện việc chuyển đổi và điều khiển hệ thống đèn 7 đoạn
 * dựa trên trạng thái hiện tại và các nút nhấn.
 */
void fsm_manual(){
    if(timer_flag10 == 1){
        setTimer10(1000); // Đặt thời gian cho hoạt động thủ công
    }
    switch(mode){
        case AUTOLIGHT:
            fsm_automatic(); // Chuyển sang chế độ tự động
            if(isButtonPressed(0) == 1){
                mode = RED_CHANGE; // Chuyển sang chế độ đèn đỏ
                setTimer3(500); // Đặt thời gian cho chế độ đèn đỏ
            }
            break;
        case RED_CHANGE:
            modifyMode(TIME_RED_tmp); // Thay đổi thời gian đèn đỏ
            if(timer_flag3 == 1){
                toggleAllRed(); // Chuyển đổi tất cả đèn sang màu đỏ
                setTimer3(500); // Đặt lại thời gian cho chế độ đèn đỏ
            }
            if(isButtonPressed(0) == 1){
                mode = YELLOW_CHANGE; // Chuyển sang chế độ đèn vàng
                setTimer3(500); // Đặt thời gian cho chế độ đèn vàng
            }
            if(isButtonPressed(1) == 1){
                TIME_RED_tmp++; // Tăng thời gian đèn đỏ
                if(TIME_RED_tmp > 99){
                    TIME_RED_tmp = 1; // Đặt lại thời gian đèn đỏ nếu quá lớn
                }
            }
            if(isButtonPressed(2) == 1){
                TIME_RED = TIME_RED_tmp; // Cập nhật thời gian đèn đỏ
            }
            break;
        case YELLOW_CHANGE:
            modifyMode(TIME_YELLOW_tmp); // Thay đổi thời gian đèn vàng
            if(timer_flag3 == 1){
                toggleAllYellow(); // Chuyển đổi tất cả đèn sang màu vàng
                setTimer3(500); // Đặt lại thời gian cho chế độ đèn vàng
            }
            if(isButtonPressed(0) == 1){
                mode = GREEN_CHANGE; // Chuyển sang chế độ đèn xanh
                setTimer4(500); // Đặt thời gian cho chế độ đèn xanh
            }
            if(isButtonPressed(1) == 1){
                TIME_YELLOW_tmp++; // Tăng thời gian đèn vàng
                if(TIME_YELLOW_tmp > 99){
                    TIME_YELLOW_tmp = 1; // Đặt lại thời gian đèn vàng nếu quá lớn
                }
            }
            if(isButtonPressed(2) == 1){
                TIME_YELLOW = TIME_YELLOW_tmp; // Cập nhật thời gian đèn vàng
            }
            break;
        case GREEN_CHANGE:
            modifyMode(TIME_GREEN_tmp); // Thay đổi thời gian đèn xanh
            if(timer_flag3 == 1){
                toggleAllGreen(); // Chuyển đổi tất cả đèn sang màu xanh
                setTimer3(500); // Đặt lại thời gian cho chế độ đèn xanh
            }
            if(isButtonPressed(0) == 1){
                mode = AUTOLIGHT; // Quay lại chế độ tự động
            }
            if(isButtonPressed(1) == 1){
                TIME_GREEN_tmp++; // Tăng thời gian đèn xanh
                if(TIME_GREEN_tmp > 99){
                    TIME_GREEN_tmp = 1; // Đặt lại thời gian đèn xanh nếu quá lớn
                }
            }
            if(isButtonPressed(2) == 1){
                TIME_GREEN = TIME_GREEN_tmp; // Cập nhật thời gian đèn xanh
                TIME_RED_tmp = TIME_GREEN_tmp + TIME_YELLOW_tmp; // Cập nhật thời gian đèn đỏ dựa trên đèn xanh và vàng
                TIME_RED = TIME_RED_tmp;
                TIME_YELLOW = TIME_YELLOW_tmp;
                TIME_GREEN = TIME_GREEN_tmp;
                updateBuffer(); // Cập nhật lại buffer hiển thị
                status = MOD_INIT; // Khởi động lại hệ thống
                status_system = 0;
            }
            break;
        default:
            break;
    }
}


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  updateBuffer();
  while (1)
  {
	  fsm_manual();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = EN0|EN1|EN2|EN3|
			REDA|REDB|YELLOWA|YELLOWB|GREENA|GREENB;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = BUT1|BUT2|BUT3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SEG1_0|SEG1_1|SEG1_2|SEG1_3|SEG1_4|SEG1_5|SEG1_6|
			SEG2_0|SEG2_1|SEG2_2|SEG2_3|SEG2_4|SEG2_5|SEG2_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timerRun();
	getKeyInput();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
