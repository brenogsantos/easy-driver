/*
 * easy_drive.c
 *
 *  Created on: Dec 9, 2021
 *      Author: breno
 */


#include "easy_driver.h"

void easyGPIOConfig(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode, f_args in){
	enum gpio_pp_pd PUPD = in.PUPD ? in.PUPD : (0x0U);
	enum gpio_otyper Otyper = in.Otyper ? in.Otyper : (0x0U);
	enum gpio_ospeed OSpeed = in.Ospeed ? in.Ospeed : (0x2U);
	return easyGPIOConfigFullSet(GPIO_Group, Pin, Mode, PUPD, Otyper, OSpeed);
}


void easyGPIOConfigFullSet(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode,
		enum gpio_pp_pd PUPD, enum gpio_otyper Otyper,
		enum gpio_ospeed Ospeed){

	RCC->AHB4ENR |= (1<<0); //Habilita o clock do GPIOA

}

















