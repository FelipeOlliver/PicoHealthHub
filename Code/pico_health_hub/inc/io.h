/**
  ******************************************************************************
  * @file    io.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of IO.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IO_H_
#define IO_H_

/* Includes ------------------------------------------------------------------*/
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "variables.h"
#include <stdio.h>

/* Defines -------------------------------------------------------------------*/
// Define o pino GP22 para o botão do joystick (entrada digital).
#define SW_PIN 22     
// Definição dos pinos para o LED RGB e os botões
const uint LED_R_PIN = 13;
const uint LED_G_PIN = 11;
const uint LED_B_PIN = 12;
const uint BTN_A_PIN = 5;
const uint BTN_B_PIN = 6;

// Define o pino do buzzer
const uint BUZZER_PIN = 10;

// Definição das cores
#define LED_OFF 0
#define LED_ON 1

// Estados
typedef enum {
    STATE_GREEN,
    STATE_YELLOW,
    STATE_RED
} led_state_t;

// Variáveis globais voláteis
volatile led_state_t current_state = STATE_GREEN;

// Função para configurar o LED RGB
void set_rgb_color(bool red, bool green, bool blue);
// Função para lidar com a mudança de estado do LED
void update_led_color(led_state_t new_state);
// Callback do temporizador para verificar o estado dos botões
bool button_repeating_timer_callback(struct repeating_timer *t);
// Inicializa os pinos
void init_gpios();

#endif /* IO_H_ */

/*******************************END OF FILE************************************/
