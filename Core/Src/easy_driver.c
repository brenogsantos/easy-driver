/*
 * easy_drive.c
 *
 *  Created on: Dec 9, 2021
 *      Author: breno
 */


#include "easy_driver.h"

#if defined(STM32H750xx)
GPIO_TypeDef *ref_gpio_group[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK};
#endif



void easyGPIOConfig(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode)
{

	easyGPIOConfigFullSet(GPIO_Group, Pin, Mode, NOPULL, OUT_PUSH_PULL, OUT_FREQ_HIGH);


}


void easyGPIOConfigFullSet(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode,
		enum gpio_pp_pd PUPD, enum gpio_otyper Otyper,
		enum gpio_ospeed Ospeed)
{
	if (GPIO_Group->OTYPER == GPIO_Group->MODER)
	{
		unsigned int N = sizeof(ref_gpio_group)/sizeof(ref_gpio_group[0]);
		for(uint8_t i = 0; i < N; i++)
		{
			if(GPIO_Group == ref_gpio_group[i]){
				RCC->AHB4ENR |= (1<<i); //Habilita o clock do GPIOA
				break;
			}

		}

	}

	if(Mode == INPUT)
	{
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin+1U));
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin));

	}
	else if(Mode == OUTPUT)
	{
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin+1U));//GPIO_Group->MODER &= ~(1UL << (Pin+Pin+1U));

		if(Otyper == OUT_PUSH_PULL) easyClearBit(&GPIO_Group->OTYPER , Pin); //GPIO_Group->OTYPER &= ~(1UL << (Pin));
		else easySetBit(&GPIO_Group->OTYPER, Pin); //GPIO_Group->OTYPER |= (1UL << (Pin));

		switch(Ospeed)
		{
			case OUT_FREQ_LOW:
				easyClearBit(&GPIO_Group->OSPEEDR, (Pin+Pin+1U));
				easyClearBit(&GPIO_Group->OSPEEDR, (Pin+Pin));
				break;
			case OUT_FREQ_MEDIUM:
				easyClearBit(&GPIO_Group->OSPEEDR, (Pin+Pin+1U));
				easySetBit(&GPIO_Group->OSPEEDR, (Pin+Pin));
				break;
			case OUT_FREQ_HIGH:
				easySetBit(&GPIO_Group->OSPEEDR, (Pin+Pin+1U));
				easyClearBit(&GPIO_Group->OSPEEDR, (Pin+Pin));
				break;
			case OUT_FREQ_VERY_HIGH:
				easySetBit(&GPIO_Group->OSPEEDR, (Pin+Pin+1U));
				easySetBit(&GPIO_Group->OSPEEDR, (Pin+Pin));
				break;
				//GPIO_Group->OSPEEDR |= (1UL<<(Pin+Pin+1U));
				//GPIO_Group->OSPEEDR &= ~(1UL << (Pin+Pin));
		}
	}

	switch(PUPD)
	{
		case NOPULL:
			easyClearBit(&GPIO_Group->PUPDR, (Pin+Pin+1U));
			easyClearBit(&GPIO_Group->PUPDR, (Pin+Pin));
			break;
		case PULLUP:
			easyClearBit(&GPIO_Group->PUPDR, (Pin+Pin+1U));
			easySetBit(&GPIO_Group->PUPDR, (Pin+Pin));
			break;
		case PULLDOWN:
			easySetBit(&GPIO_Group->PUPDR, (Pin+Pin+1U));
			easyClearBit(&GPIO_Group->PUPDR, (Pin+Pin));
			break;
			//GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin+1U));
			//GPIO_Group->PUPDR &= ~(1UL<<(Pin+Pin));
	}

}

void easyClearBit(__IO uint32_t *REG, uint8_t pos)
{
	*REG &= ~(1UL << pos);
}

void easySetBit(__IO uint32_t *REG, uint8_t pos)
{
	*REG |= (1UL << pos);
}

















