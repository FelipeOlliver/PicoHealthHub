/**
  ******************************************************************************
  * @file    task.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    30-Jan-2025
  * @brief   This file contains the headers of task.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TASK_H_
#define TASK_H_
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "animation.h"
#include "bt.h"
#include "buzzer.h"
#include "database.h"
#include "i2c.h"
#include "io.h"
#include "onewire.h"
#include "oximeter.h"
#include "ssd1306.h"
#include "stethoscope.h"
#include "uart.h"
#include "variables.h"
#include "websever.h"
#include "wifi.h"

/* Exported types ------------------------------------------------------------*/
enum
{
	INIT,
	FINISH,
	DISABLED,

	WAIT_USER_INPUT,
	SELECT_USER,
	USER_INSTRUCTIONS,

	CHECK_CONNECTION,
	WAIT_FINISH_READ,

	STANDBY,
	ATENTION,
	MEASURING,

} TaskStates;

uint8_t displayTaskState;
uint8_t ledTaskState;
uint8_t inputTaskState;
uint8_t webserverTaskState;
uint8_t bluetoothTaskState;
uint8_t mainTaskState;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TASK_Display();
void TASK_Led();
void TASK_Input();
void TASK_WebServer();
void TASK_Bluetooth();
void TASK_Main();
void TASK_Handler();




#endif /* TASK_H_ */

/*******************************END OF FILE************************************/