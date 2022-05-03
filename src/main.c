/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"

#define LEANGTH      1
#define DUMP         4*LEANGTH

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wmissing-declarations"
//#pragma GCC diagnostic ignored "-Wreturn-type"
u16 IntToChar(u16 Copy_u16Number);

int main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	   RCC_voidInitSysClock();
	   systick_init();
		RCC_voidEnableClock(RCC_APB2, 2);        /* Enable PORTA Clock */
		RCC_voidEnableClock(RCC_APB2, 4);

		RCC_voidEnableClock(RCC_APB2, 14);		/* Enable USART1 Clock */



		/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
		MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);
			/* Setting A10:RX pin as input floating */
		MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);

		MGPIO_voidSetPinDirection(GPIOA,PIN1,OUTPUT_SPEED_2MHZ_PP);
		MGPIO_voidSetPinValue(GPIOA,PIN1,1);
		MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_ANALOG);



		MUSART1_voidInit();
		ADC_VoidInit();
		volatile int x;
		//float time_val[6] ={0, 0.0100, 0.0200 , 0.0300 , 0.0400 , 0.0500}  ;
		//float sine_val[6] = {0 , 0.5878 , 0.9511  ,  0.9511 ,   0.5878 , 0.0000 };
		u8 time_val[6]={0,10,20,30,40,50};
		u8 sine_val[6]={0,59,95,95,59,0};
	///	char val1=56;
	//	char val2=89;
		int i;
  // Infinite loop
		char Data[4];
  while (1)
    {
       // Add your code here.
//	  for(i=0; i<6; i++){
//	  MUSART1_voidTransmit(&time_val[i], 1);
//	 for(x=0; x<1000; x++);
//	 MUSART1_voidTransmit(&sine_val[i], 1);
//	 for(x=0; x<1000; x++);
//	  }
//
//
//	  for(x=0; x<10000; x++);
//    }
	//  MUSART1_voidTransmit("65");
	  sprintf(Data,"%d",ADC_u16ReadChannelPoll(0));
	  MUSART1_voidTransmit(Data,4);
	  MUSART1_voidTransmit("\n",1);

}
}

u16 IntToChar(u16 Copy_u16Number)
{

	u16 Local_u16_Remaining;
	u16 Local_u16_Reverse = 1;
	u8 Local_u8_FinalReverse;
	u16 value = 0;

	if (Copy_u16Number == 0)
	{
		value = (Copy_u16Number + '0');
	}
	else
	{
		while (Copy_u16Number != 0)
		{
			Local_u16_Remaining = Copy_u16Number % 10;
			Local_u16_Reverse = Local_u16_Reverse * 10 + Local_u16_Remaining;
			Copy_u16Number /= 10;
		}
		while (Local_u16_Reverse != 1)
		{
			Local_u8_FinalReverse = Local_u16_Reverse % 10;
			value = (Local_u8_FinalReverse + '0');
			Local_u16_Reverse /= 10;
		}
	}
	return value;
}

//#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
