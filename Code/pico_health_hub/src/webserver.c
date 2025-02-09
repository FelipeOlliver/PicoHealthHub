/**
  ******************************************************************************
  * @file    webserver.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Webserver functions.
  ******************************************************************************
  */
 #include "webserver.h"

 
void init_webserver()
{
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    // Configure SSI and CGI handler
    ssi_init(); 
    printf("SSI Handler initialised\n");
    cgi_init();
    printf("CGI Handler initialised\n");
}