/*
 * easy_drive.c
 *
 *  Created on: Dec 9, 2021
 *      Author: breno
 */


#include "easy_driver.h"

void easyGPIOConfig(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode)
{

	RCC->AHB4ENR |= (1<<0); //Habilita o clock do GPIOA



	unsigned int keepBits = 0xFFFFFFFFU;
	unsigned int b = 0x1;
	unsigned int c;

	c = keepBits | b;
	c = keepBits & b;
	c = keepBits ^ (b<<3);

	easyGPIOConfigFullSet(GPIO_Group, Pin, Mode, NOPULL, OUT_PUSH_PULL, OUT_FREQ_HIGH);


}


void easyGPIOConfigFullSet(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode,
		enum gpio_pp_pd PUPD, enum gpio_otyper Otyper,
		enum gpio_ospeed Ospeed)
{

	RCC->AHB4ENR |= (1<<0); //Habilita o clock do GPIOA
	if(Mode == INPUT){
		easyClearBit(GPIO_Group->MODER, (Pin+Pin+1U));
		easyClearBit(GPIO_Group->MODER, (Pin+Pin));

		GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin+1U));
		GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin));
		return;
	}
		//GPIO_Group->MODER &= ~((1UL << (Pin+Pin+1U)) | (1UL << (Pin+Pin)));
	else if(Mode == OUTPUT)easyClearBit(GPIO_Group->MODER, (Pin+Pin+1U));
		//GPIO_Group->MODER &= ~(1UL << (Pin+Pin+1U));

	if(Otyper == OUT_PUSH_PULL) easyClearBit(GPIO_Group->OTYPER , Pin);
		//GPIO_Group->OTYPER &= ~(1UL << (Pin));
	else easySetBit(GPIO_Group->OTYPER, Pin);
		//GPIO_Group->OTYPER |= (1UL << (Pin));

	switch(Ospeed)
	{
		case OUT_FREQ_LOW:
			easyClearBit(GPIO_Group->OSPEEDR, (Pin+Pin+1U));
			easyClearBit(GPIO_Group->OSPEEDR, (Pin+Pin));
			break;
		case OUT_FREQ_MEDIUM:
			easyClearBit(GPIO_Group->OSPEEDR, (Pin+Pin+1U));
			easySetBit(GPIO_Group->OSPEEDR, (Pin+Pin));
			break;
		case OUT_FREQ_HIGH:
			easySetBit(GPIO_Group->OSPEEDR, (Pin+Pin+1U));
			easyClearBit(GPIO_Group->OSPEEDR, (Pin+Pin));
			break;
		case OUT_FREQ_VERY_HIGH:
			easySetBit(GPIO_Group->OSPEEDR, (Pin+Pin+1U));
			easySetBit(GPIO_Group->OSPEEDR, (Pin+Pin));
	}


	GPIO_Group->OSPEEDR |= (1UL<<(Pin+Pin+1U));
	GPIO_Group->OSPEEDR &= ~(1UL << (Pin+Pin));


	GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin+1U));
	GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin));


}

void easyClearBit(uint32_t *REG, uint8_t pos)
{
	REG &= ~(1UL << pos);
}

void easySetBit(uint32_t *REG, uint8_t pos)
{
	REG |= (1UL << pos);
}

















