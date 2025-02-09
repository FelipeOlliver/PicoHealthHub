/**
  ******************************************************************************
  * @file    io.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   IO functions.
  ******************************************************************************
  */
#include "io.h"

// Inicializa os pinos
void init_gpios() {
    // LED RGB como saída
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    // Botões como entrada com pull-up
    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);
    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_B_PIN);

    // Inicializa o pino do buzzer como saída (inicialmente em baixo)
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);

    // Configura o pino do botão do joystick como entrada digital com pull-up interno.
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN); // Habilita o pull-up interno para garantir leitura estável.

}

// Função para configurar o LED RGB
void set_rgb_color(bool red, bool green, bool blue) {
    gpio_put(LED_R_PIN, red);
    gpio_put(LED_G_PIN, green);
    gpio_put(LED_B_PIN, blue);
}

// Função para lidar com a mudança de estado do LED
void update_led_color(led_state_t new_state) {
    switch (new_state) {
        case STATE_GREEN:
            set_rgb_color(LED_OFF, LED_ON, LED_OFF);
            break;
        case STATE_YELLOW:
            set_rgb_color(LED_ON, LED_ON, LED_OFF);
            break;
        case STATE_RED:
            set_rgb_color(LED_ON, LED_OFF, LED_OFF);
            break;
    }
    current_state = new_state;
}

// Callback do temporizador para verificar o estado dos botões
bool button_repeating_timer_callback(struct repeating_timer *t) {
    static absolute_time_t last_press_time_a = 0;
    static absolute_time_t last_press_time_b = 0;
    static bool button_a_last_state = false;
    static bool button_b_last_state = false;

    // Verifica o botão A
    bool button_a_pressed = !gpio_get(BTN_A_PIN);
    if (button_a_pressed && !button_a_last_state &&
        absolute_time_diff_us(last_press_time_a, get_absolute_time()) > 200000) {
        last_press_time_a = get_absolute_time();
        button_a_last_state = true;
        UserInputData.buttonAState = 0x01;

        update_led_color(STATE_YELLOW);  // Sempre muda para amarelo

        printf("Botão A pressionado (Amarelo)\n");
    } else if (!button_a_pressed) {
        button_a_last_state = false;
    }

    // Verifica o botão B
    bool button_b_pressed = !gpio_get(BTN_B_PIN);
    if (button_b_pressed && !button_b_last_state &&
        absolute_time_diff_us(last_press_time_b, get_absolute_time()) > 200000) {
        last_press_time_b = get_absolute_time();
        button_b_last_state = true;

        update_led_color(STATE_RED); // Sempre muda para vermelho

        printf("Botão B pressionado (Vermelho)\n");
    } else if (!button_b_pressed) {
        button_b_last_state = false;
    }

    return true;
}