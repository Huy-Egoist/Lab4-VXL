/*
 * buttonlab4.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Admin
 */

#include "buttonlab4.h"

// Mảng cờ và trạng thái cho từng nút
int Button_flag[NUM_BUTTONS] = {0};
int KeyReg0[NUM_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg1[NUM_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg2[NUM_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int KeyReg3[NUM_BUTTONS] = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE};
int timerforKeyPress[NUM_BUTTONS] = {200, 200, 200, 200};

// Hàm kiểm tra nếu một nút được nhấn
int isButtonPressed(int button_index) {
	if (Button_flag[button_index] == 1) {
		Button_flag[button_index] = 0;
		return 1;
	}
	return 0;
}

// Hàm đặt cờ cho việc nhấn nút
void subKeyProcess(int button_index) {
	Button_flag[button_index] = 1;
}

// Hàm lấy đầu vào cho tất cả các nút
void getKeyInput() {
	for (int i = 0; i < NUM_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
	}

	// Đọc giá trị từng nút
	KeyReg2[0] = HAL_GPIO_ReadPin(Button_1_GPIO_Port, Button_1_Pin);
//	KeyReg2[1] = HAL_GPIO_ReadPin(Button2_GPIO_Port, Button2_Pin);
//	KeyReg2[2] = HAL_GPIO_ReadPin(Button3_GPIO_Port, Button3_Pin);
//	KeyReg2[3] = HAL_GPIO_ReadPin(Button_Test_GPIO_Port, Button_Test_Pin);

	for (int i = 0; i < NUM_BUTTONS; i++) {
		// Kiểm tra nếu trạng thái ổn định
		int stableState = (KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i]);

		// Kiểm tra sự thay đổi trạng thái của nút
		int stateChanged = stableState && (KeyReg3[i] != KeyReg2[i]);
		KeyReg3[i] = stateChanged ? KeyReg2[i] : KeyReg3[i];

		// Xử lý nhấn nút
		if (stateChanged && (KeyReg2[i] == PRESSED_STATE)) {
			subKeyProcess(i);
			timerforKeyPress[i] = 200;
		}
	}

	for (int i = 0; i < NUM_BUTTONS; i++) {
		// Xử lý nhấn giữ (long press)
		int stablePressed = (KeyReg2[i] == PRESSED_STATE) && (timerforKeyPress[i] == 0);
		if (stablePressed) {
			subKeyProcess(i);
			timerforKeyPress[i] = 200;
		}
		// Giảm bộ đếm nếu nút đang được nhấn
		timerforKeyPress[i] = (KeyReg2[i] == PRESSED_STATE) ? timerforKeyPress[i] - 1 : 200;
	}
}


