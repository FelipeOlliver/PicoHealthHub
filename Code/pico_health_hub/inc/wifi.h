/**
  ******************************************************************************
  * @file    wifi.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of wifi.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WIFI_H_
#define WIFI_H_

#include <stdio.h>
#include <stdbool.h> 
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// Definições de configuração 
#define MAX_WIFI_CONNECT_RETRIES 3
#define WIFI_TIMEOUT_MS 5000
#define WIFI_SSID "YOUR_WIFI_SSID"         // Substitua pelo seu SSID
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"   // Substitua pela sua senha

// Definições de estado
typedef enum {
    WIFI_DISCONNECTED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_ERROR
} wifi_status_t;

// Protótipos das funções
bool wifi_init();
bool wifi_connect();
void wifi_disconnect();
wifi_status_t wifi_get_status();  // Adicionado: Retorna o status da conexão Wi-Fi


#endif /* WIFI_H_ */

/*******************************END OF FILE************************************/