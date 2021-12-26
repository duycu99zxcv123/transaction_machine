/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "CLCD.h"
#include <stdio.h>
#include "KEYPAD.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
CLCD_Name LCD1;
char LCD_send[16];
char Key;

char accountUser[] = "20172514";
char passwordUser[] = "080799";
char accountType[8];
char passwordType[6];
char CodeType[6];
char Code1[] = "123456080799";
char Code2[] = "123789080799";

char classInfo1Reason1[3][21] = {"Software Technology","123456","Full class"};
char classInfo1Reason2[3][21] = {"Software Technology","123456","Coincident date"};
char classInfo1Reason3[3][21] = {"Software Technology","123456","Credit limitation"};

char classInfo2Reason1[3][21] = {"Digital processing","123789","Full class"};
char classInfo2Reason2[3][21] = {"Digital processing","123789","Coincident date"};
char classInfo2Reason3[3][21] = {"Digital processing","123789","Credit limitation"};

int classType1 = 0;
int classType2 = 0;
int classOrder = 0;
int classCount = 0;
unsigned int currentPosition = 0;

KEYPAD_Name KeyPad;
char KEYMAP[NUMROWS][NUMCOLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */
	CLCD_8BIT_Init(&LCD1, 20, 4, CS_GPIO_Port, CS_Pin, EN_GPIO_Port, EN_Pin,
									D0_GPIO_Port, D0_Pin, D1_GPIO_Port, D1_Pin,
									D2_GPIO_Port, D2_Pin, D3_GPIO_Port, D3_Pin,
									D4_GPIO_Port, D4_Pin, D5_GPIO_Port, D5_Pin,
									D6_GPIO_Port, D6_Pin, D7_GPIO_Port, D7_Pin);
									
	KEYPAD3X4_Init(&KeyPad, KEYMAP, GPIOA, GPIO_PIN_4, GPIOA, GPIO_PIN_5, GPIOA, GPIO_PIN_6, 
																	GPIOA, GPIO_PIN_0, GPIOA, GPIO_PIN_1,
																	GPIOA, GPIO_PIN_2, GPIOA, GPIO_PIN_3);		
																
		
		Login: CLCD_Clear(&LCD1);
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, "Please Login!");
			
			while (1) {
				if (HAL_GPIO_ReadPin(ConfirmBtn_GPIO_Port, ConfirmBtn_Pin) == 1) {
					break;
				}
				HAL_Delay(100);
			}
		
		TypeAgain: currentPosition = 0;
		CLCD_Clear(&LCD1);
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, "Type account: ");
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		CLCD_SetCursor(&LCD1, currentPosition, 1);
		CLCD_CursorOn(&LCD1);
		Key = KEYPAD3X4_Readkey(&KeyPad);
		if (Key == '*') {
					CLCD_CursorOff(&LCD1);
			currentPosition = 0;
					goto TypeAgain;
				}
		if (Key == '#') {
					CLCD_CursorOff(&LCD1);
			currentPosition = 0;
					goto Login;
				}
		if (Key) {
			
			accountType[currentPosition] = Key;
			CLCD_WriteChar(&LCD1, Key);
			currentPosition++;
		}
		HAL_Delay(100);
		if (currentPosition == 8) {
			currentPosition = 0;
			CLCD_CursorOff(&LCD1);
			break;
		}
		
  }
	
	Key = NULL;
			while (1) {
				if (HAL_GPIO_ReadPin(ConfirmBtn_GPIO_Port, ConfirmBtn_Pin) == 1) {
					break;
				}
				Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '#') {
				break;
			} 
			if(Key == '*') {
				break;
			} 
				
				HAL_Delay(100);
			}
			if (Key == '#') {
				goto Login;
			}
			if (Key == '*') {
					
					goto TypeAgain;
				}
	
	CLCD_SetCursor(&LCD1, 0, 2);
	CLCD_WriteString(&LCD1, "Type password: ");
	
	while (1)
  {
		CLCD_SetCursor(&LCD1, currentPosition, 3);
		CLCD_CursorOn(&LCD1);
		Key = KEYPAD3X4_Readkey(&KeyPad);
		
		if (Key == '*') {
					CLCD_CursorOff(&LCD1);
			currentPosition = 0;
					goto TypeAgain;
				}
		if (Key == '#') {
					CLCD_CursorOff(&LCD1);
			currentPosition = 0;
					goto Login;
				}
		if(Key) {
			
		passwordType[currentPosition] = Key;
		CLCD_WriteString(&LCD1, "*");
			currentPosition++;
		}
		HAL_Delay(100);
		
		if (currentPosition == 6) {
			currentPosition = 0;
			CLCD_CursorOff(&LCD1);
			break;
		}
		
  }
	
	Key = NULL;
			while (1) {
				if (HAL_GPIO_ReadPin(ConfirmBtn_GPIO_Port, ConfirmBtn_Pin) == 1) {
					break;
				}
				Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '#') {
				break;
			} 
			if (Key == '*') {
					
					break;
				}
				
				HAL_Delay(100);
			}
			if (Key == '#') {
				goto Login;
			}
			if (Key == '*') {
					
					goto TypeAgain;
				}
	
	if(strcmp(accountUser, accountType)==0 && strcmp(passwordUser, passwordType)==0){
		CLCD_Clear(&LCD1);
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, "Welcome!");
		HAL_Delay(2000);
		
		ChooseFunction: CLCD_Clear(&LCD1);
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, "Tran Khuong Duy");
		CLCD_SetCursor(&LCD1, 0, 1);
		CLCD_WriteString(&LCD1, "20172514 DTVT08-K62");
		CLCD_SetCursor(&LCD1, 0, 2);
		CLCD_WriteString(&LCD1, "1.Apply Certificate");
		CLCD_SetCursor(&LCD1, 0, 3);
		CLCD_WriteString(&LCD1, "2.Register Class");
		
		Key = NULL;
		while(1) {
			Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '1' || Key == '2' || Key == '#') {
				break;
			} 
			HAL_Delay(100);
		}
		
		if (Key == '1') {
			
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Choose a objective:");
			CLCD_SetCursor(&LCD1, 0, 1);
			CLCD_WriteString(&LCD1, "1.Test TOEIC");
			CLCD_SetCursor(&LCD1, 0, 2);
			CLCD_WriteString(&LCD1, "2.Apply scholarship");
			CLCD_SetCursor(&LCD1, 0, 3);
			CLCD_WriteString(&LCD1, "3.Apply a job");
			
			Key = NULL;
		while(1) {
			Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '1' || Key == '2' || Key == '3' || Key == '#') {
				break;
			} 
			
			HAL_Delay(100);
		}
		
			if (Key == '1') {

				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Confirm:");
				CLCD_SetCursor(&LCD1, 4, 1);
				CLCD_WriteString(&LCD1, "Tran Khuong Duy");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "SHSV: 20172514");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Birthday: 8-7-1999");
				HAL_Delay(3000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "In: Vinh Phuc");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "Is student of class:");
				CLCD_SetCursor(&LCD1, 4, 2);
				CLCD_WriteString(&LCD1, "DTVT08-K62");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Program: DHCQ");
				HAL_Delay(4000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Objective:");
				CLCD_SetCursor(&LCD1, 4, 1);
				CLCD_WriteString(&LCD1, "Test TOEIC");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "Expiry date:");
				CLCD_SetCursor(&LCD1, 4, 3);
				CLCD_WriteString(&LCD1, "1-1-2022");
				HAL_Delay(3000);
				
			} else if (Key == '2') {
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Confirm:");
				CLCD_SetCursor(&LCD1, 4, 1);
				CLCD_WriteString(&LCD1, "Tran Khuong Duy");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "SHSV: 20172514");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Birthday: 8-7-1999");
				HAL_Delay(3000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "In: Vinh Phuc");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "Is student of class:");
				CLCD_SetCursor(&LCD1, 4, 2);
				CLCD_WriteString(&LCD1, "DTVT08-K62");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Program: DHCQ");
				HAL_Delay(4000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Objective:");
				CLCD_SetCursor(&LCD1, 3, 1);
				CLCD_WriteString(&LCD1, "Apply scholarship");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "Expiry date:");
				CLCD_SetCursor(&LCD1, 3, 3);
				CLCD_WriteString(&LCD1, "1-1-2022");
				HAL_Delay(3000);
			} else if (Key == '3') { 
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Confirm:");
				CLCD_SetCursor(&LCD1, 4, 1);
				CLCD_WriteString(&LCD1, "Tran Khuong Duy");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "SHSV: 20172514");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Birthday: 8-7-1999");
				HAL_Delay(3000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "In: Vinh Phuc");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "Is student of class:");
				CLCD_SetCursor(&LCD1, 4, 2);
				CLCD_WriteString(&LCD1, "DTVT08-K62");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "Program: DHCQ");
				HAL_Delay(4000);
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Objective:");
				CLCD_SetCursor(&LCD1, 4, 1);
				CLCD_WriteString(&LCD1, "Apply a job");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "Expiry date:");
				CLCD_SetCursor(&LCD1, 4, 3);
				CLCD_WriteString(&LCD1, "1-1-2022");
				HAL_Delay(3000);

			} else {
				goto ChooseFunction;
				
			}
			
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Press Confirm to");
			CLCD_SetCursor(&LCD1, 2, 1);
			CLCD_WriteString(&LCD1, "print certificate!");
			
			Key = NULL;
			while (1) {
				if (HAL_GPIO_ReadPin(ConfirmBtn_GPIO_Port, ConfirmBtn_Pin) == 1) {
					break;
				}
				Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '#') {
				break;
			} 
				
				HAL_Delay(100);
			}
			if (Key == '#') {
				goto ChooseFunction;
			}
			
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Printing...");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_Delay(2000);
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Print successful");
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_Delay(2000);
			
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Do you want to");
			CLCD_SetCursor(&LCD1, 0, 1);
			CLCD_WriteString(&LCD1, "select the other");
			CLCD_SetCursor(&LCD1, 0, 2);
			CLCD_WriteString(&LCD1, "transaction?");
			
			Key = NULL;
			while(1) {
				Key = KEYPAD3X4_Readkey(&KeyPad);
				if(Key == '*' || Key == '#') {
					break;
				} 
				HAL_Delay(100);
			}
			
			if (Key == '*') {
				goto ChooseFunction;
			} else {
				goto Login;
			}
			
		} else if (Key == '2') {
			
			RegisterClass: CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "1.Register new class");
			CLCD_SetCursor(&LCD1, 0, 1);
			CLCD_WriteString(&LCD1, "2.View classes");
			
			Key = NULL;
			while(1) {
				Key = KEYPAD3X4_Readkey(&KeyPad);
				if(Key == '1' || Key == '2' || Key == '#') {
					break;
				} 
				HAL_Delay(100);
			}
			
			if (Key == '1') {
				
				if (classCount == 2) {
					CLCD_Clear(&LCD1);	
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "You only register");
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "up to 2 classes");
					HAL_Delay(3000);
					goto RegisterClass;
					
				}
				
				TypeCodeAgain: CLCD_Clear(&LCD1);	
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Enter class code:");
			
			while (1)
			{
				
				CLCD_SetCursor(&LCD1, currentPosition, 1);
				CLCD_CursorOn(&LCD1);
				Key = KEYPAD3X4_Readkey(&KeyPad);
				
				if (Key == '#') {
					CLCD_CursorOff(&LCD1);
					goto RegisterClass;
				}
				
				if(Key) {
				CodeType[currentPosition] = Key;
				CLCD_WriteChar(&LCD1, Key);
					currentPosition++;
				}
				HAL_Delay(100);
				
				if (currentPosition == 6) {
					currentPosition = 0;
					CLCD_CursorOff(&LCD1);
					break;
				}
			
			}

				Key = NULL;
			while (1) {
				if (HAL_GPIO_ReadPin(ConfirmBtn_GPIO_Port, ConfirmBtn_Pin) == 1) {
					break;
				}
				Key = KEYPAD3X4_Readkey(&KeyPad);
			if(Key == '#') {
				break;
			} 
				
				HAL_Delay(100);
			}
			if (Key == '#') {
				goto RegisterClass;
			}
		
			if (strcmp(Code1, CodeType) == 0 && classOrder != 12) {
				
				if (classCount == 0) {
					classOrder = 12;
					
				}
				
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Class Name: ");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "Software technology");
				HAL_Delay(3000);
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Choose a reason:");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "1.Full class");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "2.Coincident date");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "3.Credit limitation");
				
				Key = NULL;
				while(1) {
					Key = KEYPAD3X4_Readkey(&KeyPad);
					if(Key == '1' || Key == '2' || Key == '3' || Key == '#') {
						break;
					} 
					
					HAL_Delay(100);
				}
				
				if (Key == '1') {
					classType1 = 11;
					classCount++;
				} else if (Key == '2') {
					classCount++;
					classType1 = 12;
				} else if (Key == '3') {
					classCount++;
					classType1 = 13;
				} else {
					classOrder = 0;
					goto RegisterClass;
				}
				  HAL_Delay(1000);
				
		} else if (strcmp(Code2, CodeType) == 0 && classOrder != 21) {
			if (classCount == 0) {
					classOrder = 21;
					
				}
				
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Class Name: ");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "Digital processing");
				HAL_Delay(3000);
				CLCD_Clear(&LCD1);
				CLCD_SetCursor(&LCD1, 0, 0);
				CLCD_WriteString(&LCD1, "Choose a reason:");
				CLCD_SetCursor(&LCD1, 0, 1);
				CLCD_WriteString(&LCD1, "1.Full class");
				CLCD_SetCursor(&LCD1, 0, 2);
				CLCD_WriteString(&LCD1, "2.Coincident date");
				CLCD_SetCursor(&LCD1, 0, 3);
				CLCD_WriteString(&LCD1, "3.Credit limitation");
				
				Key = NULL;
				while(1) {
					Key = KEYPAD3X4_Readkey(&KeyPad);
					if(Key == '1' || Key == '2' || Key == '3' || Key == '#') {
						break;
					} 
					
					HAL_Delay(100);
				}
				
				if (Key == '1') {
					classType2 = 21;
					classCount++;
				} else if (Key == '2') {
					classCount++;
					classType2 = 22;
				} else if (Key == '3') {
					classCount++;
					classType2 = 23;
				} else {
					goto RegisterClass;
				}
				  HAL_Delay(1000);
				
		} else if ((strcmp(Code1, CodeType) == 0 && classOrder == 12 && classType1 != 0) || (strcmp(Code2, CodeType) == 0 && classOrder == 21 && classType2 != 0)) {
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "You already");
			CLCD_SetCursor(&LCD1, 0, 1);
			CLCD_WriteString(&LCD1, "signed up this class");
			HAL_Delay(3000);
			goto TypeCodeAgain;
			
		} else {
			CLCD_Clear(&LCD1);
			CLCD_SetCursor(&LCD1, 0, 0);
			CLCD_WriteString(&LCD1, "Incorrect code");
			CLCD_SetCursor(&LCD1, 0, 1);
			CLCD_WriteString(&LCD1, "Please try again");
			HAL_Delay(3000);
			goto TypeCodeAgain;
		} 
			
					CLCD_Clear(&LCD1);
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "Sent Registration");
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "Please wait ");
					CLCD_SetCursor(&LCD1, 0, 2);
					CLCD_WriteString(&LCD1, "to response!");
					HAL_Delay(3000);
				
					
					CLCD_Clear(&LCD1);
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "Do you want to");
					CLCD_SetCursor(&LCD1, 0, 1);
					CLCD_WriteString(&LCD1, "select the other");
					CLCD_SetCursor(&LCD1, 0, 2);
					CLCD_WriteString(&LCD1, "transaction?");
					
					Key = NULL;
					while(1) {
						Key = KEYPAD3X4_Readkey(&KeyPad);
						if(Key == '*' || Key == '#') {
							break;
						} 
						HAL_Delay(100);
					}
			
					if (Key == '*') {
						goto ChooseFunction;
					} else {
						goto Login;
					}
		
			} else if (Key == '2') {
				
				if (classCount == 1) {
						if (classOrder == 12) {
							
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "1.");
							CLCD_SetCursor(&LCD1, 1, 1);
							CLCD_WriteString(&LCD1, "Software technology");
							Key = NULL;
					while(1) {
						Key = KEYPAD3X4_Readkey(&KeyPad);
						if(Key == '1' || Key == '#') {
							break;
						} 
						HAL_Delay(100);
					}
			
					if (Key == '1') {
						if (classType1 == 11) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType1 == 12) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
							
							}  else {
									goto RegisterClass;
								
							}
					
						} else {
							
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "1.Digital processing");
							
							Key = NULL;
					while(1) {
						Key = KEYPAD3X4_Readkey(&KeyPad);
						if(Key == '1' || Key == '#') {
							break;
						} 
						HAL_Delay(100);
					}
			
					if (Key == '1') {
						if (classType2 == 21) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType2 == 22) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
					} else {
						
									goto RegisterClass;
						
					}						
							
						}
				} else if (classCount == 2) {
					
							if (classOrder == 12) {
							
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "1.");
							CLCD_SetCursor(&LCD1, 1, 1);
							CLCD_WriteString(&LCD1, "Software technology");
							CLCD_SetCursor(&LCD1, 0, 2);
							CLCD_WriteString(&LCD1, "2.Digital processing");
								
							Key = NULL;
					while(1) {
						Key = KEYPAD3X4_Readkey(&KeyPad);
						if(Key == '1' || Key == '2' || Key == '#') {
							break;
						} 
						HAL_Delay(100);
					}
			
					if (Key == '1') {
						if (classType1 == 11) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType1 == 12) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
							
							} else if (Key == '2'){
								if (classType2 == 21) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType2 == 22) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
							} else {
								
									goto RegisterClass;
								
							}
					
						} else {
							
							CLCD_Clear(&LCD1);
							CLCD_SetCursor(&LCD1, 0, 0);
							CLCD_WriteString(&LCD1, "1.Digital processing");
							CLCD_SetCursor(&LCD1, 0, 1);
							CLCD_WriteString(&LCD1, "2.");
							CLCD_SetCursor(&LCD1, 1, 2);
							CLCD_WriteString(&LCD1, "Software technology");
							
							Key = NULL;
					while(1) {
						Key = KEYPAD3X4_Readkey(&KeyPad);
						if(Key == '1' || Key == '2' || Key == '#') {
							break;
						} 
						HAL_Delay(100);
					}
			
					if (Key == '1') {
						if (classType2 == 21) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType2 == 22) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Digital processing");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123789");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
					} else if (Key == '2'){
								if (classType1 == 11) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 3, 3);
								CLCD_WriteString(&LCD1, "Full class");
								
								
							} else if (classType1 == 12) {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Coincident date");
								
							} else {
								CLCD_Clear(&LCD1);
								CLCD_SetCursor(&LCD1, 0, 0);
								CLCD_WriteString(&LCD1, "Software technology");
								CLCD_SetCursor(&LCD1, 0, 1);
								CLCD_WriteString(&LCD1, "Code: 123456");
								CLCD_SetCursor(&LCD1, 0, 2);
								CLCD_WriteString(&LCD1, "Reason: ");
								CLCD_SetCursor(&LCD1, 0, 3);
								CLCD_WriteString(&LCD1, "Credit limitation");
							}
					}		 else {
									goto RegisterClass;
								
					}				
							
						}
				} else {
					CLCD_Clear(&LCD1);
					CLCD_SetCursor(&LCD1, 0, 0);
					CLCD_WriteString(&LCD1, "You dont register");
					CLCD_SetCursor(&LCD1, 3, 1);
					CLCD_WriteString(&LCD1, "any class!");
			}
				
								Key = NULL;
								while(1) {
									Key = KEYPAD3X4_Readkey(&KeyPad);
									if(Key == '#') {
										break;
									} 
									HAL_Delay(100);
								}
								
								if (Key == '#') {
									goto RegisterClass;
								}
		} else {
			goto ChooseFunction;
		}
	} else{
		
		goto Login;
	}
	
} else {
		CLCD_Clear(&LCD1);
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1,"Incorrect account");
		CLCD_SetCursor(&LCD1, 0, 1);
		CLCD_WriteString(&LCD1,"or password");
		CLCD_SetCursor(&LCD1, 0, 2);
		CLCD_WriteString(&LCD1,"Please try again");
		HAL_Delay(3000);
		goto TypeAgain;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|D5_Pin
                          |D6_Pin|D7_Pin|EN_Pin|CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|D0_Pin|D1_Pin
                          |D2_Pin|D3_Pin|D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ConfirmBtn_Pin */
  GPIO_InitStruct.Pin = ConfirmBtn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ConfirmBtn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 D5_Pin
                           D6_Pin D7_Pin EN_Pin CS_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|D5_Pin
                          |D6_Pin|D7_Pin|EN_Pin|CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 D0_Pin D1_Pin
                           D2_Pin D3_Pin D4_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|D0_Pin|D1_Pin
                          |D2_Pin|D3_Pin|D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
