/**
  ******************************************************************************
  * @file    variables.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the variables of project.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VARIABLES_H_
#define VARIABLES_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "io.h"

typedef struct {
 float temperature;
 int systolic;
 int diastolic;
 int spo2;
 int heartRate;
 uint32_t timestamp;
} MeasurementData;

typedef struct{
 uint8_t buttonAState;
 uint8_t buttonBState;
 uint8_t joystickButtonState;
 int joystickX;
 int joystickY;
} UserInputData;

UserInputData_t UserInputData;

typedef struct {
 char name[50];
 char email[100];
 uint32_t userId;
}UserData;

UserData_t UserData;

typedef struct{
 uint8_t ledStatus;
 uint8_t buzzerState;
} FeedbackData;

static const char *tags[] = {
    "temperature", "systolicPressure", "diastolicPressure", "spo2Level", "heartRate"
};
static int numtags = sizeof(tags) / sizeof(tags[0]);

#endif /* VARIABLES_H_ */

/*******************************END OF FILE************************************/