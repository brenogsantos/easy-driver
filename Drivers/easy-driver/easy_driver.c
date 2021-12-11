/*
 * easy_drive.c
 *
 *  Created on: Dec 9, 2021
 *      Author: breno
 */


#include "easy_driver.h"

#if defined(STM32H750xx)
GPIO_TypeDef *ref_gpio_group[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK};
USART_TypeDef *ref_uart_group[] = {USART1, USART2, USART3, UART4, UART5, USART6, UART7, UART8};
#endif



void easyGPIOConfig(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode)
{
	easyGPIOConfigFullSet(GPIO_Group, Pin, Mode, NOPULL, OUT_PUSH_PULL, OUT_FREQ_HIGH);

}


void easyGPIOConfigFullSet(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode,
		enum gpio_pp_pd PUPD, enum gpio_otyper Otyper,
		enum gpio_ospeed Ospeed)
{

	easyGPIOCheckClock(GPIO_Group);

	if(Mode == INPUT)
	{
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin+1U));
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin));
	}
	else if(Mode == OUTPUT)
	{
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin+1U));//GPIO_Group->MODER &= ~(1UL << (Pin+Pin+1U));
		easySetBit(&GPIO_Group->MODER, (Pin+Pin));

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
	else if(Mode == ALTERNATE_FUNCTION)
	{
		easySetBit(&GPIO_Group->MODER, (Pin+Pin+1));
		easyClearBit(&GPIO_Group->MODER, (Pin+Pin));
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

void easyGPIOCheckClock(GPIO_TypeDef *GPIO_Group)	//it enables the gpiogroup clock
{
	if (GPIO_Group->OTYPER == GPIO_Group->MODER)	//check if its off
	{
		unsigned int N = sizeof(ref_gpio_group)/sizeof(ref_gpio_group[0]);
		for(uint8_t i = 0; i < N; i++)
		{
			if(GPIO_Group == ref_gpio_group[i]){
				RCC->AHB4ENR |= (1<<i); //Habilita o clock do GPIO (H7 series)
				break;
			}
		}
	}
}

void easyGPIOSetState(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, uint8_t state)
{
	  if(state == 0) easySetBit(&GPIO_Group->BSRR, (Pin + 16)); //reseta
	  else easySetBit(&GPIO_Group->BSRR, (Pin));
}

uint8_t easyGPIOReadState(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin){

	uint8_t state;

	if(easyReadBit(&GPIO_Group->MODER, (Pin+Pin+1)) == 0U && easyReadBit(&GPIO_Group->MODER, (Pin+Pin)) == 0U)
	{	//INPUT
		state = easyReadBit(&GPIO_Group->IDR, Pin);
	}
	else if(easyReadBit(&GPIO_Group->MODER, (Pin+Pin+1)) == 0U && easyReadBit(&GPIO_Group->MODER, (Pin+Pin)) == 1U)
	{	//OUTPUT
		state = easyReadBit(&GPIO_Group->ODR, Pin);
	}

	return state;
}

void easyGPIOToggle(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin)
{

	if(easyReadBit(&GPIO_Group->MODER, (Pin+Pin+1)) == 0U && easyReadBit(&GPIO_Group->MODER, (Pin+Pin)) == 1U)
	{
		if(GPIO_Group->ODR)easyGPIOSetState(GPIO_Group, Pin, 0);
		else easyGPIOSetState(GPIO_Group, Pin, 1);
	}

}


//UART

void easyUSARTConfig(USART_TypeDef *USART_Group, GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin_TX, enum gpio_pin Pin_RX)
{

	uint8_t afr_pos_tx, afr_pos_rx;

	easyGPIOConfigFullSet(GPIO_Group, Pin_TX, ALTERNATE_FUNCTION, NOPULL,0,0);
	easyGPIOConfigFullSet(GPIO_Group, Pin_RX, ALTERNATE_FUNCTION, NOPULL,0,0);

	if(Pin_TX > 7) {
		afr_pos_tx = 1;
		Pin_TX -= 8;
	}
	else afr_pos_tx = 0;

	if(Pin_RX > 7) {
		afr_pos_rx = 1;
		Pin_RX -= 8;
	}
	else afr_pos_rx = 0;





	/** AF 0100 da H7 series **/
	Pin_TX = (4*Pin_TX);
	Pin_RX = (4*Pin_RX);
	//TX
	easyClearBit(&GPIO_Group->AFR[afr_pos_tx], Pin_TX + 3);
	easySetBit(&GPIO_Group->AFR[afr_pos_tx], Pin_TX + 2);
	easyClearBit(&GPIO_Group->AFR[afr_pos_tx], Pin_TX + 1);
	easyClearBit(&GPIO_Group->AFR[afr_pos_tx], Pin_TX);

	//RX
	easyClearBit(&GPIO_Group->AFR[afr_pos_rx], Pin_RX + 3);
	easySetBit(&GPIO_Group->AFR[afr_pos_rx], Pin_RX + 2);
	easyClearBit(&GPIO_Group->AFR[afr_pos_rx], Pin_RX + 1);
	easyClearBit(&GPIO_Group->AFR[afr_pos_rx], Pin_RX);
	/** AF 0100 da H7 series **/


	easyUSARTCheckClock(USART_Group);

	USART_Group->CR1 = 0x00;
	easySetBit(&USART_Group->CR1, 0);
	USART_Group->BRR |= (3 << 0) | (34 << 4);	//baudrate 115200
	easySetBit(&USART_Group->CR1, 2);	//REN


}

void easyUSARTCheckClock(USART_TypeDef *USART_Group)	//it enables the gpiogroup clock
{
	unsigned int N = sizeof(ref_uart_group)/sizeof(ref_uart_group[0]);
	uint8_t i;
	for(i = 0; i < N; i++)
	{
		if(USART_Group == ref_uart_group[i]){
			break;
		}
	}
	switch (i){
		case 0:
			easySetBit(&RCC->APB2ENR, 4);
			break;
		case 1:
			easySetBit(&RCC->APB1LENR, 17);
			break;
		case 2:
			easySetBit(&RCC->APB1LENR, 18);
			break;
		case 3:
			easySetBit(&RCC->APB1LENR, 19);
			break;
		case 4:
			easySetBit(&RCC->APB1LENR, 20);
			break;
		case 5:
			easySetBit(&RCC->APB2ENR, 5);
			break;
		case 6:
			easySetBit(&RCC->APB1LENR, 30);
			break;
		case 7:
			easySetBit(&RCC->APB1LENR, 31);
			break;

	}

}

void easyUSARTSendChar(USART_TypeDef *USART_Group, uint8_t c)
{
	easySetBit(&USART_Group->CR1, 3);	//TEN
	USART_Group->TDR = c;
	while (!(USART_Group->ISR & (1<<6)));

}

void easyUSARTSendString(USART_TypeDef *USART_Group, char *string)
{
	while (*string) easyUSARTSendChar(USART_Group, *string++);
}
































void easyClearBit(__IO uint32_t *REG, uint8_t pos)
{
	*REG &= ~(1UL << pos);
}

void easySetBit(__IO uint32_t *REG, uint8_t pos)
{
	*REG |= (1UL << pos);
}

uint8_t easyReadBit(__IO uint32_t *REG, uint8_t pos)
{
	uint8_t bit;
	bit = (*REG >> pos) & 1U;
	return bit;
}

















