/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Bassam
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "HAL_sevenSegment.h"
#include "DIO_interface.h"
#include "HAL_LED.h"


int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, 2); // Enable clock for GPIOA (A:2 B:3 C:4)
	RCC_voidEnableClock(RCC_APB2, 3); // Enable clock for GPIOD
	RCC_voidEnableClock(RCC_APB2, 4); // Enable clock for GPIOC
	LED_void_init(GPIOB, PIN0);
	LED_void_init(GPIOA, PIN9);

	while(1){
      // test 1
	/*	LED_void_on(GPIOB, PIN0);
		LED_void_on(GPIOA, PIN9);
		for(int i =0; i<10000; i++);
		LED_void_off(GPIOB, PIN0);
		LED_void_off(GPIOA, PIN9);
		for(int i =0; i<10000; i++);  */
		// test 2
		LED_void_toggle(GPIOB, PIN0);
		LED_void_toggle(GPIOA, PIN9);
		for(int i =0; i<10000; i++);

	}
}
