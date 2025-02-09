/**
  ******************************************************************************
  * @file    cgi.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   CGI functions.
  ******************************************************************************
  */

#include "cgi.h"
#include <stdio.h>

// CGI handler para Exportar Dados
const char *cgi_export_data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    printf("Requisição para Exportar Dados recebida.\n");
    // Aqui você implementaria a lógica para exportar os dados dos sensores.
    // Por enquanto, apenas redireciona de volta para a página principal.
    return "/index.shtml";
}

// CGI handler para Atualizar Dados
const char *cgi_update_data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    printf("Requisição para Atualizar Dados recebida.\n");
    // Aqui você implementaria a lógica para atualizar os dados dos sensores
    // Por enquanto, apenas redireciona de volta para a página principal.
    return "/index.shtml";
}

// tCGI Struct
// Preencha com todas as requisições CGI e seus respectivos handlers
const tCGI cgi_handlers[] = {
    {"/exportData.cgi", cgi_export_data_handler},
    {"/updateData.cgi", cgi_update_data_handler}
};
int num_cgi_handlers = sizeof(cgi_handlers) / sizeof(cgi_handlers[0]);

// Inicializa o manipulador CGI
void cgi_init(void) {
    http_set_cgi_handlers(cgi_handlers, num_cgi_handlers);
}