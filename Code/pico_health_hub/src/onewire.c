/**
  ******************************************************************************
  * @file    onewire.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Onewire functions.
  ******************************************************************************
  */
#include "onewire.h"

// Função para definir o pino 1-Wire como saída
void onewire_set_as_output(bool state) {
    gpio_set_dir(ONE_WIRE_PIN, GPIO_OUT);
    gpio_put(ONE_WIRE_PIN, state);
}

// Função para definir o pino 1-Wire como entrada
void onewire_set_as_input() {
    gpio_set_dir(ONE_WIRE_PIN, GPIO_IN);
}

// Inicializa o pino 1-Wire
void init_onewire(){
    gpio_init(ONE_WIRE_PIN);
    onewire_set_as_input(); // Começa como entrada para evitar curto
}

// Função para gerar um pulso de reset
bool onewire_reset() {
    onewire_set_as_output(false);
    sleep_us(480); // > 480us
    onewire_set_as_input();
    sleep_us(70); // 15-60us
    bool presence = !gpio_get(ONE_WIRE_PIN); // Sensor should pull low
    sleep_us(410); // >480us recovery
    return presence;
}

// Função para escrever um bit
void onewire_write_bit(bool bit) {
    onewire_set_as_output(false);
    if (bit) {
        // Short low pulse for '1'
        sleep_us(6);
        onewire_set_as_input();
        sleep_us(64);
    } else {
        // Long low pulse for '0'
        sleep_us(60);
        onewire_set_as_input();
        sleep_us(10);
    }
}

// Função para ler um bit
bool onewire_read_bit() {
    onewire_set_as_output(false);
    sleep_us(2);
    onewire_set_as_input();
    sleep_us(15);
    bool bit = gpio_get(ONE_WIRE_PIN);
    sleep_us(45);
    return bit;
}

// Função para escrever um byte
void onewire_write_byte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        onewire_write_bit(data & 1);
        data >>= 1;
    }
}

// Função para ler um byte
uint8_t onewire_read_byte() {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        data |= (onewire_read_bit() << i);
    }
    return data;
}

// Função para ler o ROM Code (endereço único) do sensor
uint64_t onewire_read_rom_code() {
    uint64_t rom_code = 0;
    onewire_reset();
    onewire_write_byte(READ_ROM); // Command to read ROM
    for (int i = 0; i < 8; i++) {
        ((uint8_t*)&rom_code)[i] = onewire_read_byte();
    }
    return rom_code;
}

// Função para iniciar a conversão de temperatura
void onewire_convert_temperature() {
    onewire_reset();
    onewire_write_byte(0xCC); // Skip ROM
    onewire_write_byte(CONVERT_T); // Convert T
}

// Função para ler o Scratchpad (dados do sensor)
void onewire_read_scratchpad(uint8_t *data, int len) {
    onewire_reset();
    onewire_write_byte(0xCC); // Skip ROM
    onewire_write_byte(READ_SCRATCHPAD); // Read Scratchpad
    for (int i = 0; i < len; i++) {
        data[i] = onewire_read_byte();
    }
}