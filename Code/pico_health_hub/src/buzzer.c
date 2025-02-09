/**
  ******************************************************************************
  * @file    buzzer.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Buzzer functions.
  ******************************************************************************   
  */

#include "buzzer.h"

 void Beep(uint16_t numberOfBeeps, uint16_t timeHigh, uint16_t timeLow) {
    beep.numOfBeeps = numberOfBeeps;
    beep.timeHigh = timeHigh;
    beep.timeLow = timeLow;

    // Configura o pino do buzzer como PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    // Determina qual fatia PWM (PWM slice) o pino está conectado
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Calcula a frequência e o ciclo de trabalho (duty cycle)
    float freq = 1000.0 / (timeHigh + timeLow); // Frequência em Hz
    uint32_t wrap = 125000000 / freq; // system clock / desired frequency

    // Configura o gerador PWM
    pwm_set_clkdiv(slice_num, DIVIDER_PWM);
    pwm_set_wrap(slice_num, PERIOD);
    pwm_set_gpio_level(BUZZER_PIN, buzzer_level); // Ciclo de trabalho de 50%
    pwm_set_enabled(slice_num, true);
    /*pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, wrap / 2); // Ciclo de trabalho de 50%
    pwm_set_enabled(slice_num, true);*/

    // Delay para o número de beeps
    sleep_ms((timeHigh + timeLow) * numberOfBeeps);

    // Desabilita o PWM para silenciar o buzzer
    pwm_set_enabled(slice_num, false);
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_SIO); // Retorna o pino à sua função original
    gpio_put(BUZZER_PIN, 0); // Garante que o pino esteja em baixo
}