/**
  ******************************************************************************
  * @file    onewire.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of Onewire.
  ******************************************************************************
  */
 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ONEWIRE_H_
#define ONEWIRE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Define os pinos
#define ONE_WIRE_PIN 2 // GP02

// Define os comandos
#define READ_ROM 0x33
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE
#define WRITE_SCRATCHPAD 0x4E

// Função para ler o ROM Code (endereço único) do sensor
uint64_t onewire_read_rom_code();

// Função para iniciar a conversão de temperatura
void onewire_convert_temperature();

// Função para ler o Scratchpad (dados do sensor)
void onewire_read_scratchpad(uint8_t *data, int len);






#endif /* ONEWIRE_H_ */

/*******************************END OF FILE************************************/