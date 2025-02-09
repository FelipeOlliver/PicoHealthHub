/**
  ******************************************************************************
  * @file    buzzer.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains all the functions prototypes and headers for the buzzer.h
  *          interface firmware driver.
  ******************************************************************************   
  */
#ifndef BUZZER_H_
#define BUZZER_H_

/* Includes ------------------------------------------------------------------*/
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "io.h"

uint16_t buzzer_level = 500;       // Nível inicial do PWM (duty cycle)
const uint16_t PERIOD = 2000;   // Período do PWM (valor máximo do contador)
const float DIVIDER_PWM = 16.0; // Divisor fracional do clock para o PWM

// Estrutura para configuração do beep
typedef struct {
    uint8_t numOfBeeps;
    uint16_t timeHigh;  // Tempo em que o pino está em nível alto (ms)
    uint16_t timeLow;   // Tempo em que o pino está em nível baixo (ms)
} BeepConfig_t;

// Variável global para a configuração do beep
BeepConfig_t beep;

// Protótipo da função Beep
void Beep(uint16_t numberOfBeeps, uint16_t timeHigh, uint16_t timeLow);

#endif /* BUZZER_H_ */