/**
  ******************************************************************************
  * @file    animation.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   This file contains the headers of animation.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ANIMATION_H_
#define ANIMATION_H_

 #include "i2c.h"
 #include "ssd1306.h"

 void initial_animation(void);
 void select_user_animation(void);
 void user_instructions_animation(void);

#endif /* ANIMATION_H_ */

/*******************************END OF FILE************************************/