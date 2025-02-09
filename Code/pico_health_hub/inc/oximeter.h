/**
  ******************************************************************************
  * @file    oximeter.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of oximeter.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OXIMETER_H_
#define OXIMETER_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "i2c.h"

// Define o endereço I2C do MAX30102
#define MAX30102_ADDR 0x57  // Endereço padrão (7-bit)

// Definições de Registradores
#define REG_INTR_STATUS_1  0x00
#define REG_INTR_ENABLE_1  0x01
#define REG_FIFO_WR_PTR    0x02
#define REG_OVERFLOW_CTR   0x03
#define REG_FIFO_RD_PTR    0x04
#define REG_FIFO_DATA      0x07
#define REG_MODE_CONFIG    0x08
#define REG_SPO2_CONFIG    0x09
#define REG_LED_CONFIG     0x0A

// Tamanho do buffer para dados do FIFO
#define FIFO_DATA_SIZE 4 // Bytes por amostra (IR + Red)
#define FIFO_BUFFER_LEN 32 // Tamanho do buffer FIFO

// Buffer para dados do MAX30102
uint8_t max30102_fifo_buffer[FIFO_BUFFER_LEN * FIFO_DATA_SIZE];

// Protótipos das funções
void init_max30102();
void read_max30102_data(uint8_t *buffer, int len);


#endif /* OXIMETER_H_ */

/*******************************END OF FILE************************************/