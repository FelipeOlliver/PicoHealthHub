/**
  ******************************************************************************
  * @file    cgi.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of cgi.
  ******************************************************************************
  */


#ifndef CGI_H
#define CGI_H

#include "lwip/apps/httpd.h"
#include <stdio.h>

// Protótipos das funções CGI handler
const char *cgi_export_data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char *cgi_update_data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

// tCGI Struct
// Preencha com todas as requisições CGI e seus respectivos handlers
extern const tCGI cgi_handlers[];
extern int num_cgi_handlers;

// Inicializa o manipulador CGI
void cgi_init(void);

#endif /* CGI_H_ */

/*******************************END OF FILE************************************/