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
	  uint32_t j = 0;

		for(int i = 0; i < 1000; i ++){
			j++;
		}
	  if(GPIOE->IDR>>3 == 0){
		 easyGPIOToggle(GPIOA, PIN_1);
	  }

  }

}

