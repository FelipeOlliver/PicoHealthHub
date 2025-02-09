/**
  ******************************************************************************
  * @file    i2c.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   I2C functions.
  ******************************************************************************
  */
 #include "i2c.h"

 void init_i2c(void) {
    i2c_init(I2C_PORT, 400000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}