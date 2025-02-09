/**
  ******************************************************************************
  * @file    pico_health_hub.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    30-Jan-2025
  * @brief   Main function.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "task.h"



int main()
{
    //Initialize peripherals
    init_gpios();
    init_i2c(void);
    init_display();    
    init_onewire();
    init_adc_modules();
    setup_adc_dma();
    setup_uart_dma()
    init_max30102();
    wifi_init();
    

    //Initialize task state
	displayTaskState = DISABLED;
	ledTaskState = DISABLED;
	inputTaskState = DISABLED;
	webserverTaskState = DISABLED;
	bluetoothTaskState = DISABLED;
	mainTaskState = DISABLED;

	while(1)
	{
		TASK_Handler();
	}
}
