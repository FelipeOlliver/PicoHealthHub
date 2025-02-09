/**
  ******************************************************************************
  * @file    database.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Database functions.
  ******************************************************************************
  */
#include "database.h"

#define FIREBASE_OK       0
#define FIREBASE_ERROR    -1
#define FIREBASE_TIMEOUT  -2

// Define o pino para o LED (substitua pelo pino correto)
#define LED_PIN CYW43_WL_GPIO_LED_PIN

// Mutex para sincronização com a biblioteca ESP
static struct mutex lwesp_mutex;

/* LwESP Callback functions */
static uint32_t dns_addr;
static bool is_dns_setted = false;
void dns_discover_cb(const char* domain_name, const ip4_addr_t* ip_addr, void* arg) {
    if (domain_name != NULL && ip_addr != NULL) {
        printf("[LwESP] DNS discover domain: %s, ip: %"PRIu32"\r\n", domain_name, ip4_addr_get_u32(ip_addr));
        dns_addr = ip4_addr_get_u32(ip_addr);
        is_dns_setted = true;
    }
}

// LwESP default callback function
void lwesp_default_callback_function(lwesp_evt_t* evt) {
    switch (evt->evt) {
        case LWESP_EVT_INIT_FINISH: {
            printf("[LwESP] LwESP initialization complete!\r\n");
            break;
        }
        case LWESP_EVT_WIFI_AP_CONNECTED: {
            lwesp_ip_t ip_addr;
            evt->data.wifi_ap_connected.ssid[evt->data.wifi_ap_connected.ssid_len] = 0;
            printf("[LwESP] WIFI: Connected to AP: %s!\r\n", evt->data.wifi_ap_connected.ssid);
            if (lwesp_get_ip_addr(&ip_addr, 1) == lwespOK) {
                printf("[LwESP] WIFI: IP address: %d.%d.%d.%d\r\n", (int)ip_addr.addr[0], (int)ip_addr.addr[1], (int)ip_addr.addr[2], (int)ip_addr.addr[3]);
            }
            break;
        }
        case LWESP_EVT_WIFI_AP_DISCONNECTED: {
            evt->data.wifi_ap_disconnected.ssid[evt->data.wifi_ap_disconnected.ssid_len] = 0;
            printf("[LwESP] WIFI: Disconnected from AP: %s!\r\n", evt->data.wifi_ap_disconnected.ssid);
            break;
        }
        default:
            printf("LwESP callback: %d\r\n", (int)evt->evt);
        break;
    }
}

// Função para construir o corpo da requisição JSON (AJUSTADO)
static void build_json_body(char* json_body, const SensorData* data) {
    sprintf(json_body,
        "{"
        "\"userID\":\"%s\","
        "\"name\":\"%s\","
        "\"email\":\"%s\","
        "\"time\":\"%s\","
        "\"temperature\":%.1f,"
        "\"systolic_pressure\":%d,"
        "\"diastolic_pressure\":%d,"
        "\"spo2\":%d,"
        "\"heart_rate\":%d"
        "}",
        data->userId, data->userName, data->userEmail, data->timestamp,
        data->temperature, data->systolicPressure, data->diastolicPressure,
        data->spo2Level, data->heartRate
    );
}

// Função para lidar com o estado do LwESP
static void lwesp_process_data(void* arg) {
    while (true) {
        mutex_lock_blocking(&lwesp_mutex);
        lwesp_process();
        mutex_unlock(&lwesp_mutex);
        sleep_ms(1); // Delay pequeno para não consumir toda a CPU
    }
}

// Inicializa a biblioteca LwESP
bool firebase_init() {
    // Inicializa o LED
    cyw43_arch_gpio_init(LED_PIN);
    cyw43_arch_gpio_put(LED_PIN, 1);

    // Cria o mutex
    mutex_init(&lwesp_mutex);

     // Inicializa a biblioteca LwESP
    if (lwesp_init(lwesp_default_callback_function, 1) != lwespOK) {
        printf("[LwESP] Erro ao inicializar a biblioteca LwESP!\r\n");
        return false;
    }
    // Crie uma thread para processar os dados do LwESP
    thread_t thread;
    thread_create(&thread, lwesp_process_data, NULL, 0, NULL);

    // Aguarda a inicialização do LwESP
    while (lwesp_is_initialized() == 0) {
        printf("[LwESP] Aguardando a inicialização do LwESP...\r\n");
        sleep_ms(1000);
    }
    return true;
}

// Envia os dados para o Firebase
bool firebase_send_data(SensorData data) {
    err_t err;
    char json_body[512]; // Aumente o tamanho se necessário
    char b64_buffer[72]; //Buffer para o Header Autenticado
    char firebase_url[200]; //Buffer para a Url do Banco
    lwesp_netconn_p conn; // LwESP TCP/IP network connection structure

   // Formata a URL do Firebase com o caminho e o token de autenticação
    snprintf(firebase_url, sizeof(firebase_url), "https://%s%s?auth=%s", FIREBASE_HOST, FIREBASE_PATH, FIREBASE_AUTH);
    printf("Url Firebase: %s", firebase_url);
    // Constrói o corpo da requisição JSON
    build_json_body(json_body, &data);
    printf("Json Body: %s", json_body);
    // Converte o nome de usuário e senha para base64
    char auth_string[100];
    snprintf(auth_string, sizeof(auth_string), ":%s", FIREBASE_AUTH); // Deixa somente a senha

    size_t encoded_len = base64_encode((uint8_t*)auth_string, strlen(auth_string), b64_buffer, sizeof(b64_buffer));
    if (encoded_len == 0) {
        printf("Erro ao codificar para Base64!\r\n");
        return FIREBASE_ERROR;
    }
    b64_buffer[encoded_len] = '\0'; // Garante que a string termine com um nulo
    printf("Base64 Autenticado: %s", b64_buffer);
    // Agora construa o cabeçalho de autorização
    char auth_header[100];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Basic %s\r\n", b64_buffer);

    // Cria uma nova conexão
    printf("Criando uma conexão...\r\n");
    mutex_lock_blocking(&lwesp_mutex);
    conn = lwesp_netconn_new(LWESP_NETCONN_TYPE_TCP);
    mutex_unlock(&lwesp_mutex);
    if (conn == NULL) {
         printf("Erro ao criar a conexão!\r\n");
        return FIREBASE_ERROR;
    }
    /* Resolve Firebase Host */
    printf("Resolvendo URL %s\r\n", FIREBASE_HOST);
    lwesp_dns_resolve(FIREBASE_HOST, dns_discover_cb, NULL);
    
    //Aguarda para resolver o IP
    absolute_time_t timeout_time = delayed_by_ms(get_absolute_time(), 5000);
    while(!is_dns_setted && absolute_time_diff_us(get_absolute_time(), timeout_time) > 0){
           printf("Aguardando DNS\n");
          cyw43_arch_gpio_put(LED_PIN, 0); // Apaga o LED
            sleep_ms(250);
            cyw43_arch_gpio_put(LED_PIN, 1); // Acende o LED
             sleep_ms(250);
    }

    if (!is_dns_setted) {
        printf("Não conseguiu resolver URL!\r\n");
        return FIREBASE_TIMEOUT;
    }
    cyw43_arch_gpio_put(LED_PIN, 1); // Garante que o LED esteja aceso
    is_dns_setted = false;
    // Conecta-se ao host do Firebase
    printf("Conectando a porta 443\r\n");
     mutex_lock_blocking(&lwesp_mutex);
    err = lwesp_netconn_connect(conn, dns_addr, 443); //Firebase usa a porta 443 para HTTPS
     mutex_unlock(&lwesp_mutex);

    if (err != lwespOK) {
        printf("Erro ao conectar: %d!\r\n", (int)err);
        return FIREBASE_ERROR;
    }
    // Conexão estabelecida

    // Envia a requisição HTTP
   printf("Enviando a requisição HTTP\r\n");
    mutex_lock_blocking(&lwesp_mutex);
    err = lwesp_netconn_write(conn,
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "%s" /* Autenticação */
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        FIREBASE_PATH,
        FIREBASE_HOST,
        auth_header,
        strlen(json_body),
        json_body);

     mutex_unlock(&lwesp_mutex);

    if (err != lwespOK) {
          printf("Erro ao escrever dados para o servidor: %d\r\n", err);
        lwesp_netconn_close(conn); // Garante que a conexão seja fechada em caso de erro
        return FIREBASE_ERROR;
    }

      // Aguarda a resposta
    printf("Aguardando a resposta\r\n");
    /* Set a timeout of 10 seconds for receive */
    lwesp_netconn_set_recv_timeout(conn, 10000);
     mutex_lock_blocking(&lwesp_mutex);
    err = lwesp_netconn_receive(conn);
      mutex_unlock(&lwesp_mutex);
    if (err != lwespOK) {
           printf("Erro ao ler resposta do servidor: %d\r\n", err);
        lwesp_netconn_close(conn); // Garante que a conexão seja fechada em caso de erro
        return FIREBASE_ERROR;
    }
    /* Check for data */
    printf("Validando os dados da leitura de conexão com firebase");
     mutex_lock_blocking(&lwesp_mutex);
    if (conn->pbuf != NULL) {
          printf("Dados Recebidos da conexão com firebase:\r\n%s\r\n", (char*)conn->pbuf->payload);
        lwesp_netconn_pbuf_free(conn->pbuf);       /* Free data buffer */
        conn->pbuf = NULL;
    }else{
        printf("Sem dados para leitura, a partir da conexão com firebase!\r\n");
        return FIREBASE_ERROR;
    }
     mutex_unlock(&lwesp_mutex);

    // Fecha a conexão
   printf("Fechando a conexão\r\n");
   mutex_lock_blocking(&lwesp_mutex);
    err = lwesp_netconn_close(conn);
    mutex_unlock(&lwesp_mutex);
    if (err != lwespOK) {
           printf("Erro ao fechar a conexão: %d\r\n", err);
          return FIREBASE_ERROR;
    }
    return FIREBASE_OK;
}