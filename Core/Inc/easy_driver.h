/*
 * easy_drive.h
 *
 *  Created on: Dec 9, 2021
 *      Author: breno
 */

#ifndef INC_EASY_DRIVE_H_
#define INC_EASY_DRIVE_H_


#include "stm32h7xx.h"

#define GPIO_USED 1




#if GPIO_USED

#define easyGPIOConfigFullSet(...) easyGPIOConfig((f_args){__VA_ARGS__});


enum gpio_pin {
	PIN_0 = ((uint16_t)0x0001),  /* Pin 0 selected    */
	PIN_1 = ((uint16_t)0x0002),  /* Pin 1 selected    */
	PIN_2 = ((uint16_t)0x0004),  /* Pin 2 selected    */
	PIN_3 = ((uint16_t)0x0008),  /* Pin 3 selected    */
	PIN_4 = ((uint16_t)0x0010),  /* Pin 4 selected    */
	PIN_5 = ((uint16_t)0x0020),  /* Pin 5 selected    */
	PIN_6 = ((uint16_t)0x0040),  /* Pin 6 selected    */
	PIN_7 = ((uint16_t)0x0080),  /* Pin 7 selected    */
	PIN_8 = ((uint16_t)0x0100),  /* Pin 8 selected    */
	PIN_9 = ((uint16_t)0x0200),  /* Pin 9 selected    */
	PIN_10 = ((uint16_t)0x0400),  /* Pin 10 selected   */
	PIN_11 = ((uint16_t)0x0800),  /* Pin 11 selected   */
	PIN_12 = ((uint16_t)0x1000),  /* Pin 12 selected   */
	PIN_13 = ((uint16_t)0x2000), /* Pin 13 selected   */
	PIN_14 = ((uint16_t)0x4000),  /* Pin 14 selected   */
	PIN_15 = ((uint16_t)0x8000),  /* Pin 15 selected   */
	PIN_All = ((uint16_t)0xFFFF),  /* All pins selected */

	PIN_MASK = (0x0000FFFFU) /* PIN mask for assert test */
};

enum gpio_mode {
	INPUT = (0x0U),
	OUTPUT = (0x1U),
	AF = (0x10U),
	ANALOG = (0x3U)

};

enum gpio_otyper {
	OUT_PUSH_PULL = (0x0U),
	OUT_OPEN_DRAIN = (0x1U)
};

enum gpio_ospeed {
	OUT_FREQ_LOW = (0x0U),  /*!< Low speed     */
	OUT_FREQ_MEDIUM = (0x1U),  /*!< Medium speed  */
	OUT_FREQ_HIGH = (0x2U),  /*!< Fast speed    */
	OUT_FREQ_VERY_HIGH = (0x3U)  /*!< High speed    */
};

enum gpio_pp_pd{
	NOPULL = (0x0U),   /*!< No Pull-up or Pull-down activation  */
	PULLUP = (0x1U),  /*!< Pull-up activation                  */
	PULLDOWN = (0x2U)   /*!< Pull-down activation                */
};

#define  GPIO_MODE_IT_RISING                    (0x11110000U)   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                   (0x11210000U)   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING            (0x11310000U)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

#define  GPIO_MODE_EVT_RISING                   (0x11120000U)   /*!< External Event Mode with Rising edge trigger detection               */
#define  GPIO_MODE_EVT_FALLING                  (0x11220000U)   /*!< External Event Mode with Falling edge trigger detection              */
#define  GPIO_MODE_EVT_RISING_FALLING           (0x11320000U)   /*!< External Event Mode with Rising/Falling edge trigger detection       */



typedef struct{

	enum gpio_pp_pd PUPD;
	enum gpio_otyper Otyper;
	enum gpio_ospeed Ospeed;

}f_args;




void easyGPIOConfig(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode, f_args in);

void easyGPIOConfigFullSet(GPIO_TypeDef *GPIO_Group, enum gpio_pin Pin, enum gpio_mode Mode,
		enum gpio_pp_pd PUPD, enum gpio_otyper Otyper,
		enum gpio_ospeed Ospeed);

#endif







#endif /* INC_EASY_DRIVE_H_ */
