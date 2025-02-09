/**
  ******************************************************************************
  * @file    i2c.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of I2C.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef I2C_H_
#define I2C_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

/* Defines -------------------------------------------------------------------*/
// Define os pinos da interface I2C
#define SDA_PIN 14
#define SCL_PIN 15
#define I2C_PORT i2c1

// Inicializa os pinos do I2C
void init_i2c(void);


#endif /* I2C_H_ */

/*******************************END OF FILE************************************/