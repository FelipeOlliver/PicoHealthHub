/**
  ******************************************************************************
  * @file    database.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of database.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/httpd.h"  

#include <stdio.h> 

#include "lwesp/lwesp.h"
#include "lwesp/lwesp_http.h"
#include "lwesp/lwesp_netconn.h"

#include "lwip/dns.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
#include "lwip/apps/sntp.h"

// Definições de configuração
#define FIREBASE_HOST "your-project-id.firebaseio.com" // Substitua pelo seu Host do Firebase
#define FIREBASE_AUTH "your-firebase-secret"    // Substitua pelo seu segredo do Firebase
#define FIREBASE_PATH "/data.json"              // Caminho para salvar os dados

// Struct para os dados a serem enviados
typedef struct {
    char userId[10];
    char userName[50];
    char userEmail[100];
    char timestamp[30];
    float temperature;
    int systolicPressure;
    int diastolicPressure;
    int spo2Level;
    int heartRate;
} SensorData;

// Funções
bool firebase_init();
bool firebase_send_data(SensorData data);



#endif /* DATABASE_H_ */

/*******************************END OF FILE************************************/