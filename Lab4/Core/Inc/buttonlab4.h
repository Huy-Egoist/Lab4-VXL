/*
 * buttonlab4.h
 *
 *  Created on: Nov 27, 2024
 *      Author: Admin
 */

#ifndef INC_BUTTONLAB4_H_
#define INC_BUTTONLAB4_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define NUM_BUTTONS	4

extern int Button_flag[];

int isButtonPressed();
void getKeyInput();

#endif /* INC_BUTTONLAB4_H_ */
