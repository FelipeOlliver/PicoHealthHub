/**
  ******************************************************************************
  * @file    uart.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   UART functions.
  ******************************************************************************
  */
 #include "uart.h"

 // Rotina de interrupção (IRQ) para o DMA (UART)
void uart_dma_handler() {
    // Limpa o sinalizador de interrupção DMA (UART)
    dma_hw->ints0 = 1u << UART_DMA_CHANNEL;
    uart_dma_complete = true;  // Sinaliza que a leitura UART foi concluída
}

// Função para configurar a UART e DMA
void setup_uart_dma() {
    // Inicializa a UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Configura o DMA para a UART
    int uart_dma_channel = dma_claim_unused_channel(true);
    dma_channel_config uart_dma_config = dma_channel_get_default_config(uart_dma_channel);

    // Configura as opções do canal DMA
    channel_config_set_transfer_data_size(&uart_dma_config, DMA_SIZE_8);  // UART transfere bytes
    channel_config_set_read_increment(&uart_dma_config, false);         // Não incrementa o endereço de leitura (UART)
    channel_config_set_write_increment(&uart_dma_config, true);        // Incrementa o endereço de escrita (buffer)
    channel_config_set_dreq(&uart_dma_config, uart_get_dreq(UART_ID));    // Define o DREQ para a UART

    // Configura a interrupção
    dma_channel_set_irq0_enabled(uart_dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, uart_dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    // Configura o canal DMA
    dma_channel_configure(
        uart_dma_channel,
        &uart_dma_config,
        uart_buffer,                // Endereço de destino (buffer)
        &uart_hw->dr,             // Endereço de origem (UART data register)
        UART_BUFFER_SIZE - 1,    // Número de transferências (tamanho do buffer -1 para o nulo)
        true                      // Inicia imediatamente
    );
}

// Função para processar os dados da UART (pressão arterial)
BloodPressureData process_uart_data() {
    BloodPressureData bp_data = {0}; // Inicializa com zeros
    char *token;
    int i = 0;

    // Garante que a string termine com um nulo
    uart_buffer[UART_BUFFER_SIZE - 1] = '\0';

    // Separa a string em tokens usando "," como delimitador
    token = strtok(uart_buffer, ",");
    while (token != NULL && i < 3) {
        int value = atoi(token);  // Converte o token para inteiro
        switch (i) {
            case 0:
                bp_data.systolic = value;
                break;
            case 1:
                bp_data.diastolic = value;
                break;
            case 2:
                bp_data.pulse = value;
                break;
        }
        token = strtok(NULL, ","); // Próximo token
        i++;
    }

    // Classifica a pressão arterial
    if (bp_data.systolic < 90 || bp_data.diastolic < 60) {
        strcpy(bp_data.classification, "Hypotension");
    } else if (bp_data.systolic >= 90 && bp_data.systolic <= 119 && bp_data.diastolic >= 60 && bp_data.diastolic <= 79) {
        strcpy(bp_data.classification, "Desired");
    } else if (bp_data.systolic >= 120 && bp_data.systolic <= 139 || bp_data.diastolic >= 80 && bp_data.diastolic <= 89) {
        strcpy(bp_data.classification, "Prehypertension");
    } else if (bp_data.systolic >= 140 && bp_data.systolic <= 159 || bp_data.diastolic >= 90 && bp_data.diastolic <= 99) {
        strcpy(bp_data.classification, "Stage 1 Hypertension");
    } else if (bp_data.systolic >= 160 && bp_data.systolic <= 179 || bp_data.diastolic >= 100 && bp_data.diastolic <= 109) {
        strcpy(bp_data.classification, "Stage 2 Hypertension");
    } else if (bp_data.systolic >= 180 || bp_data.diastolic >= 110) {
        strcpy(bp_data.classification, "Hypertensive Crisis");
    } else {
        strcpy(bp_data.classification, "Unknown");
    }

    return bp_data;
}

