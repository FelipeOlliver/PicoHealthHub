/**
  ******************************************************************************
  * @file    animation.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   Animation functions.
  ******************************************************************************
  */
 #include "animation.h"

 #define SLEEPTIME 25

 void initial_animation(void) {
    char buf[8];

    ssd1306_draw_string(&disp, 8, 0, 2, "BEM VINDO");
    ssd1306_show(&disp);
    ssd1306_draw_string(&disp, 8, 24, 2, "AO PICO");
    ssd1306_show(&disp);
    ssd1306_draw_string(&disp, 8, 48, 2, "HEALTH HUB");
    ssd1306_show(&disp);
    sleep_ms(3000);
    ssd1306_clear(&disp);

    for(int y=0; y<31; ++y) {
        ssd1306_draw_line(&disp, 0, y, 127, y);
        ssd1306_show(&disp);
        sleep_ms(SLEEPTIME);
        ssd1306_clear(&disp);
    }

    for(int y=0, i=1; y>=0; y+=i) {
        ssd1306_draw_line(&disp, 0, 31-y, 127, 31+y);
        ssd1306_draw_line(&disp, 0, 31+y, 127, 31-y);
        ssd1306_show(&disp);
        sleep_ms(SLEEPTIME);
        ssd1306_clear(&disp);
        if(y==32) i=-1;
    }

    ssd1306_draw_string(&disp, 20, 0, 1, "PICO HEALTH HUB");
    ssd1306_show(&disp);
    ssd1306_draw_line(&disp, 0, 16, 127, 16);
    ssd1306_show(&disp);
    ssd1306_draw_string(&disp, 22, 32, 1, "Aperte \"A\" para");
    ssd1306_draw_string(&disp, 48, 48, 1, "iniciar");
    ssd1306_show(&disp);
    sleep_ms(800);

}

void select_user_animation(void)
{

}

void user_instructions_animation(void)
{
    
}