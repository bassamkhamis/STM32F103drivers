

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"

#define LEANGTH      2
#define DUMP         4*LEANGTH

int main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, 2);        /* Enable PORTA Clock */
	RCC_voidEnableClock(RCC_APB2, 14);		/* Enable USART1 Clock */

	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_VidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_VidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);

	MGPIO_VidSetPinDirection(GPIOA,PIN0,OUTPUT_SPEED_2MHZ_PP);

	MUSART1_voidInit();

	volatile int x;
    float data[2] = {1,2};
	while(1)
	{
		MUSART1_voidTransmit((u8 *)data,DUMP);
		for(x=0; x<100000; x++);

		
		
		
/* 		x = MUSART1_u8Receive();
		if(x == '5')
		{
			MGPIO_VidSetPinValue(GPIOA,PIN0,HIGH);
		}
		if(x == 'r')
		{
			MGPIO_VidSetPinValue(GPIOA,PIN0,LOW);
		} */
	}

	return 0;
}
