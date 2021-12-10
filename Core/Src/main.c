#include <easy_driver.h>


int main(void)
{
	for(int i = 0; i < 1000000; i ++){

	}
	//PA1
	//RCC->AHB4ENR |= (1<<0); //Habilita o clock do GPIOA
	//GPIOA->MODER &= 0xFFFFFFF4; // pino PE1(bits 3:2) como Output (01), pino PE0(bits 1:0) como Input (00)
	//GPIOA->OTYPER &= ~((1<<1) | (1<<0));// bit (1 e 0) =0 --> Output push pull
	//GPIOA->OSPEEDR |= (1<<3) | (1<<1); // Pino A1 (bits 3:2)
	//GPIOA->PUPDR &= ~((1<<2) | (1<<3));
	easyGPIOConfig(GPIOA, PIN_1, OUTPUT);
	//PE3
	RCC->AHB4ENR |= (1<<4); //Habilita o clock do GPIOE
	GPIOE->MODER &= 0xFFFFFF3F;
	GPIOE->PUPDR |= ((1<<6) | (0<<7));


  while (1)
  {
	  uint32_t j = 0;

		for(int i = 0; i < 1000000; i ++){
			j++;
		}
	 /* if(GPIOE->IDR>>3 == 0){
		 // GPIOA->BSRR |= (1<<17);//seta PA1
	  }
	  else
		//  GPIOA->BSRR |= (1<<1);//reseta PA1
*/
  }

}

