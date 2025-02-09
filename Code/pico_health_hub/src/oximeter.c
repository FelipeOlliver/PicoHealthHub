/**
  ******************************************************************************
  * @file    oximeter.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Oximeter functions.
  ******************************************************************************
  */
 #include "oximeter.h"

 // Inicializa o sensor MAX30102 via I2C
void init_max30102() {

    // Configurações do sensor (Power Mode, SPO2 config, LED pulse amplitude)
    uint8_t write_buffer[2];

    // Reset do sensor
    write_buffer[0] = REG_MODE_CONFIG;
    write_buffer[1] = 0x40; // Reseta o sensor
    i2c_write_blocking(I2C_PORT, MAX30102_ADDR, write_buffer, 2, false);
    sleep_ms(100);

    // Configura o modo de operação
    write_buffer[0] = REG_MODE_CONFIG;
    write_buffer[1] = 0x03;  // Modo SPO2
    i2c_write_blocking(I2C_PORT, MAX30102_ADDR, write_buffer, 2, false);

    // Configura SPO2
    write_buffer[0] = REG_SPO2_CONFIG;
    write_buffer[1] = 0x27;  //  Valor de configuração típico
    i2c_write_blocking(I2C_PORT, MAX30102_ADDR, write_buffer, 2, false);

    // Configura LED
    write_buffer[0] = REG_LED_CONFIG;
    write_buffer[1] = 0x03; // Valor para corrente LED
    i2c_write_blocking(I2C_PORT, MAX30102_ADDR, write_buffer, 2, false);

    printf("MAX30102 Inicializado.\n");
}

// Leitura de dados do sensor para o buffer
void read_max30102_data(uint8_t *buffer, int len) {
    uint8_t reg = REG_FIFO_DATA;
    i2c_write_blocking(I2C_PORT, MAX30102_ADDR, reg, 1, true); // Envia endereço do registrador
    i2c_read_blocking(I2C_PORT, MAX30102_ADDR, buffer, len, false); // Lê os dados
}