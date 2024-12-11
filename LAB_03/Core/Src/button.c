/*
 * button.c
 *
 *  Created on: Nov 20, 2024
 *      Author: phong
 */

#include "button.h"

int KeyReg0[NUM_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[NUM_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[NUM_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[NUM_BUTTON] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};

int BUTTON[3]= {BUT1, BUT2, BUT3};
int TimeOutForKeyPress[NUM_BUTTON] = {500, 500, 500}; // Thời gian chờ cho mỗi nút nhấn
int button_long_pressed[NUM_BUTTON] = {0, 0, 0}; // Trạng thái nút nhấn lâu
int button_flag[NUM_BUTTON] = {0, 0, 0}; // Cờ trạng thái nút nhấn

/**
 * @brief Kiểm tra nếu nút được nhấn.
 *
 * @param index Chỉ số của nút nhấn.
 * @return 1 nếu nút được nhấn, 0 nếu không.
 */
int isButtonPressed(int index){
    if(button_flag[index] == 1){
        button_flag[index] = 0; // Đặt lại cờ sau khi kiểm tra
        return 1;
    }
    return 0;
}

/**
 * @brief Kiểm tra nếu nút được nhấn lâu.
 *
 * @param index Chỉ số của nút nhấn.
 * @return 1 nếu nút được nhấn lâu, 0 nếu không.
 */
int isButtonLongPressed(int index){
    if(button_long_pressed[index] == 1){
        button_long_pressed[index] = 0; // Đặt lại cờ sau khi kiểm tra
        return 1;
    }
    return 0;
}

/**
 * @brief Xử lý sự kiện khi nút nhấn được phát hiện.
 *
 * @param index Chỉ số của nút nhấn.
 */
void subKeyProcess(int index){
    button_flag[index] = 1; // Đặt cờ trạng thái nút nhấn
}

/**
 * @brief Đọc trạng thái nút nhấn và cập nhật trạng thái.
 */
void getKeyInput(){
    for (int i = 0; i < NUM_BUTTON; i++) {
        KeyReg2[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg0[i];
        KeyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BUTTON[i]); // Đọc trạng thái nút nhấn

        if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg2[i] != KeyReg3[i]) {
                KeyReg3[i] = KeyReg2[i];

                if (KeyReg3[i] == PRESSED_STATE) {
                    TimeOutForKeyPress[i] = 200; // Đặt thời gian chờ khi nhấn
                    subKeyProcess(i); // Xử lý nút nhấn
                }

            } else {
                TimeOutForKeyPress[i]--;
                if (TimeOutForKeyPress[i] == 0) {
                    TimeOutForKeyPress[i] = 200; // Đặt lại thời gian chờ
                    if (KeyReg3[i] == PRESSED_STATE) {
                        subKeyProcess(i); // Xử lý nút nhấn
                    }
                }
            }
        }
    }
}
