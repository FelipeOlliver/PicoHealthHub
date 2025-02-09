/**
  ******************************************************************************
  * @file    webserver.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of webserver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef WEBSERVER_H_
#define WEBSERVER_H_

/* Includes ------------------------------------------------------------------*/
#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"

void init_webserver();


#endif /* WEBSERVER_H_ */

/*******************************END OF FILE************************************/