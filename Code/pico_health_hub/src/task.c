/**
  ******************************************************************************
  * @file    task.c
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    30-Jan-2025
  * @brief   Task functions.
  ******************************************************************************
  */
 
 #include "task.h"

void TASK_Display(){
  switch (displayTaskState)
	{
		case INIT:
      initial_animation(void);
      displayTaskState = WAIT_USER_INPUT;
      inputTaskState = INIT;
		break;

		case WAIT_USER_INPUT:
			
		break;

		case SELECT_USER:
      select_user_animation(void);
      displayTaskState = WAIT_USER_INPUT;
      inputTaskState = SELECT_USER;
			
		break;

		case USER_INSTRUCTIONS:
      Beep(2,250,250);
      user_instructions_animation(void);
      displayTaskState = WAIT_USER_INPUT;
      inputTaskState = STANDBY;
			
		break;
	}

}
void TASK_Led(){
  switch (ledTaskState)
	{
		case STANDBY:
      update_led_color(STATE_GREEN);
		break;

		case ATENTION:
      update_led_color(STATE_YELLOW);
			
		break;

		case STATE_RED:
      update_led_color(STATE_GREEN);			
		break;

	}

}
void TASK_Input(){
  switch (inputTaskState)
	{
		case INIT:
      // Configura o temporizador repetitivo
      struct repeating_timer button_timer;
      add_repeating_timer_ms(100, button_repeating_timer_callback, NULL, &button_timer); // Intervalo de 100ms
      inputTaskState = WAIT_USER_INPUT;	
		break;

		case WAIT_USER_INPUT:
      if (UserInputData.buttonAState)
      {
        mainTaskState = SELECT_USER
        UserInputData.buttonAState = 0x00;
        inputTaskState = DISABLED;

      }
		
		break;

		case SELECT_USER:
      if (UserInputData.buttonBState)
      {
        strcpy(UserData.name,user_read_name);
        strcpy(UserData.email,user_read_email);
        UserData.userID = user_read_id;
        inputTaskState = DISABLED;
        mainTaskState = USER_INSTRUCTIONS;
      }
			
		break;

		case STANDBY:
			
		break;
	}

}
void TASK_WebServer(){
  switch (webserverTaskState)
	{
		case INIT:      
      wifi_connect();
      webserverTaskState = CHECK_CONNECTION;
		break;

		case CHECK_CONNECTION:
      if(wifi_get_status())
      {
        init_webserver();
        webserverTaskState = STANDBY;
      }
			
		break;

		case STANDBY:
			
		break;

	}

}
void TASK_Bluetooth(){
  switch (bluetoothTaskState)
	{
		case INIT:

		break;

		case WAIT_USER_INPUT:
			
		break;

		case SELECT_USER:
			
		break;

		case STANDBY:
			
		break;
	}

}
void TASK_Main(){
  switch (mainTaskState)
	{
		case INIT:
      displayTaskState = INIT;
      ledTaskState = STANDBY;
      mainTaskState = WAIT_USER_INPUT;
		break;

		case WAIT_USER_INPUT:
			
		break;

		case SELECT_USER:
      webserverTaskState = INIT;
      displayTaskState = SELECT_USER;
			
		break;

		case USER_INSTRUCTIONS:
      displayTaskState = USER_INSTRUCTIONS;
			
		break;
	}

}



 void TASK_Handler()
{
	TASK_Display();
  TASK_Led();
  TASK_Input();
  TASK_WebServer();
  TASK_Bluetooth();
  TASK_Main();
}