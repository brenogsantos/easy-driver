#include "../../Drivers/easy-driver/easy_driver.h"


int main(void)
{
	for(int i = 0; i < 1000000; i ++){

	}

	easyGPIOConfig(GPIOA, PIN_1, OUTPUT);
	easyGPIOConfigFullSet(GPIOE, PIN_3,INPUT, PULLUP, OUT_PUSH_PULL, OUT_FREQ_LOW);

	easyGPIOSetState(GPIOA, 1, SET);
  while (1)
  {

		uint8_t state;
		state = easyGPIOReadState(GPIOE, PIN_3);
	  if(state == 0){
		 easyGPIOToggle(GPIOA, PIN_1);
		 state = easyGPIOReadState(GPIOA, PIN_1);
	  }

  }

}

