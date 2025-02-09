/**
  ******************************************************************************
  * @file    wifi.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   WI-FI functions.
  ******************************************************************************
  */
 #include "wifi.h"

 static volatile wifi_status_t wifi_status = WIFI_DISCONNECTED;

 bool wifi_init() {
    if (cyw43_arch_init()) {
        printf("Falha ao inicializar cyw43_arch\n");
        wifi_status = WIFI_ERROR;
        return false;
    }
    cyw43_arch_enable_sta_mode();
    wifi_status = WIFI_DISCONNECTED; // Inicializa o estado como desconectado
    return true;
}

bool wifi_connect() {
    printf("Conectando-se a %s...\n", WIFI_SSID);
    wifi_status = WIFI_CONNECTING;

    for (int i = 0; i < MAX_WIFI_CONNECT_RETRIES; ++i) {
        if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, WIFI_TIMEOUT_MS)) {
            printf("Conectado a %s!\n", WIFI_SSID);
            wifi_status = WIFI_CONNECTED;
            return true;
        } else {
            printf("Falha na tentativa %d de conectar.\n", i + 1);
            sleep_ms(1000); // Aguarda antes de tentar novamente
        }
    }

    printf("Falha ao conectar após %d tentativas.\n", MAX_WIFI_CONNECT_RETRIES);
    wifi_status = WIFI_ERROR;
    return false;
}

void wifi_disconnect() {
    cyw43_arch_disable_sta_mode();
    wifi_status = WIFI_DISCONNECTED;
    printf("Wi-Fi desconectado.\n");
}

wifi_status_t wifi_get_status() {
    return wifi_status;
}