/**
  ******************************************************************************
  * @file    adc.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   ADC functions.
  ******************************************************************************
  */
#include "adc.h"

// Função para configurar um canal ADC
void adc_channel_config(uint channel, uint pin) {
    adc_gpio_init(pin);
    adc_select_input(channel);
}

// Inicializa os pinos de ADC
void init_adc_modules(){
    // Inicializa o módulo ADC do Raspberry Pi Pico.
    // Isso prepara o ADC para ler valores dos pinos analógicos.
    adc_init();

    // Configura os pinos GPIO 26, 27 e 28 para leitura analógica do ADC.
    adc_gpio_init(VRX_PIN); // Configura GP26 (ADC0) para o eixo X do joystick.
    adc_gpio_init(VRY_PIN); // Configura GP27 (ADC1) para o eixo Y do joystick.
    adc_gpio_init(MIC_PIN); // Inicializa o pino do microfone

    // Configura a ordem dos pinos a serem lidos pelo ADC
    adc_channel_config(0, VRX_PIN);
    adc_channel_config(1, VRY_PIN);
    adc_channel_config(2, MIC_PIN); // Configura o canal para o microfone

}

// Rotina de interrupção (IRQ) para o DMA
void dma_handler() {
    // Limpa o sinalizador de interrupção DMA
    dma_hw->ints0 = 1u << ADC_DMA_CHANNEL;
    adc_dma_complete = true; // Sinaliza que a leitura do ADC foi concluída
}

// Função para configurar o ADC e DMA
void setup_adc_dma() {
    // Obtém o canal DMA e configura
    int dma_channel = dma_claim_unused_channel(true);
    dma_channel_config dma_config = dma_channel_get_default_config(dma_channel);

    // Define o ciclo de incremento para desabilitar a leitura e habilitar a escrita
    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_16);
    channel_config_set_read_increment(&dma_config, false);
    channel_config_set_write_increment(&dma_config, true);

    // Configura o destino da leitura
    channel_config_set_dreq(&dma_config, DREQ_ADC);

    // Define a interrupção ao completar a transferência
    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    // Configura o canal DMA
    dma_channel_configure(
        dma_channel,
        &dma_config,
        adc_values,    // Endereço de destino (buffer)
        &adc_hw->fifo, // Endereço de origem (FIFO do ADC)
        ADC_BUFFER_SIZE,           // Número de transferências (tamanho do buffer)
        true            // Inicia imediatamente
    );
}

// Função para processar os dados do joystick, microfone e imprimir os dados
void process_adc_data(uint16_t vrx_value, uint16_t vry_value, uint16_t mic_value, bool sw_value) {
    // Imprime os valores lidos na comunicação serial.
    printf("VRX: %u, VRY: %u, MIC: %u, SW: %d\n", vrx_value, vry_value, mic_value, sw_value);
    printf("Microphone Voltage: %.5f\n", mic_value * ADC_CONVERT);
}