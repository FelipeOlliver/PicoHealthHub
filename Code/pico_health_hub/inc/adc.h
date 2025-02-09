/**
  ******************************************************************************
  * @file    adc.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of ADC.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADC_H_
#define ADC_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "io.h"

// Definições dos pinos para o joystick,
#define VRX_PIN 26    // Define o pino GP26 para o eixo X do joystick (Canal ADC0).
#define VRY_PIN 27    // Define o pino GP27 para o eixo Y do joystick (Canal ADC1).

// Definição do pino para o microfone,
#define MIC_PIN 28  // Pino para o microfone (ADC2)

// Definições do microfone
#define ADC_VREF 3.3
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1))

// Definições para DMA
#define ADC_DMA_CHANNEL 0
#define ADC_BUFFER_SIZE 3  // VRX, VRY, MIC
uint16_t adc_values[ADC_BUFFER_SIZE];

// Variável para indicar que a leitura do ADC foi concluída
volatile bool adc_dma_complete = false;

// Função para configurar um canal ADC
void adc_channel_config(uint channel, uint pin);
// Inicializa os pinos de ADC
void init_adc_modules();

// Protótipos das funções
void setup_adc_dma();
void process_adc_data(uint16_t vrx_value, uint16_t vry_value, uint16_t mic_value, bool sw_value);




#endif /* ADC_H_ */

/*******************************END OF FILE************************************/