/**
  ******************************************************************************
  * @file    ssi.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of ssi.
  ******************************************************************************
  */

#ifndef SSI_H
#define SSI_H

#include "lwip/apps/httpd.h"  
#include "pico/cyw43_arch.h"   
#include "hardware/adc.h"     
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "variables.h"

// Definições dos nomes das tags SSI
extern const char *tags[];
extern int numtags;

uint32_t user_read_id = 0x01;
char user_read_name = {"F","e","l","i","p","e"};
char user_read_email = {"F","e","l","i","p","e"};

// Protótipo da função SSI handler
static const char *ssi_handler(const char *ssi_tag);

// Inicializa o manipulador SSI
void ssi_init();

#endif /* SSI_H_ */

/*******************************END OF FILE************************************/