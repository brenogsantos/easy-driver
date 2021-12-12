#include "../../Drivers/easy-driver/easy_driver.h"


int main(void)
{
	for(int i = 0; i < 1000000; i ++){

	}

	easyGPIOConfig(GPIOA, PIN_1, OUTPUT);
	easyGPIOConfigFullSet(GPIOE, PIN_3,INPUT, PULLUP, 0, 0);
	easyUSARTConfig(USART1, GPIOB, PIN_14, PIN_15);


	easyGPIOSetState(GPIOA, 1, SET);
  while (1)
  {

	uint8_t state;
	state = easyGPIOReadState(GPIOE, PIN_3);
	if(state == 0){
		easyGPIOToggle(GPIOA, PIN_1);
	}
	easyUSARTSendString(USART1, "deu certo\n");
	for(int i = 0; i < 1000000; i ++){
		easyUSARTprintf(USART1, "%d\n", i);
	}

  }

}

