/**
  ******************************************************************************
  * @file    uart.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of uart.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UART_H_
#define UART_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"


/* Defines -------------------------------------------------------------------*/
 // Definições para UART
#define UART_ID uart1
#define UART_TX_PIN 8
#define UART_RX_PIN 9
#define BAUD_RATE 9600
#define DATA_BITS 8
#define UART_DMA_CHANNEL 4 // Canal DMA
#define UART_BUFFER_SIZE 32 // Tamanho do buffer para acomodar os dados

/* Exported types ------------------------------------------------------------*/
// Variável para indicar que a leitura da UART foi concluída
volatile bool uart_dma_complete = false;
char uart_buffer[UART_BUFFER_SIZE];

// Struct para dados da pressão arterial
typedef struct {
    int systolic;
    int diastolic;
    int pulse;
    char classification[50]; // String para armazenar a classificação
} BloodPressureData;

// Protótipos das funções
void setup_uart_dma();
BloodPressureData process_uart_data();


#endif /* UART_H_ */

/*******************************END OF FILE************************************/
