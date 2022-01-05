/*********************************************************************************/
/* Author    : Bassam                                                       */
/* Version   : V01                                                           */
/* Date      : 5 JUN 2022                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "HAl_LED.h"


void LED_void_init(u8 copy_PORT, u8 copy_u8PIN)
{
	
			   switch(copy_PORT){
		   
		   case GPIOA:   MGPIO_VidSetPinDirection(copy_PORT,copy_u8PIN, OUTPUT_SPEED_2MHZ_PP);

					     break;

					
		
		   
		   case GPIOB:    MGPIO_VidSetPinDirection(copy_PORT,copy_u8PIN, OUTPUT_SPEED_2MHZ_PP);

						  break;
						  
						  
						  
		    case GPIOC:  MGPIO_VidSetPinDirection(copy_PORT,copy_u8PIN, OUTPUT_SPEED_2MHZ_PP);

				         break;			  
						  
			default :
                         break;
	
        }
}

void LED_void_on(u8 copy_PORT, u8 copy_u8PIN)
{
	MGPIO_VidSetPinValue( copy_PORT, copy_u8PIN,HIGH);
}

void LED_void_off(u8 copy_PORT, u8 copy_u8PIN)
{ 
    MGPIO_VidSetPinValue(copy_PORT,  copy_u8PIN,LOW);
	
}


void LED_void_toggle(u8 copy_PORT, u8 copy_u8PIN)
{
	u8 LOC_VAL = MGPIO_u8GetPinValue(copy_PORT, copy_u8PIN);
	if(1 == LOC_VAL){
		MGPIO_VidSetPinValue(copy_PORT,copy_u8PIN,LOW);
	}

	else{
		MGPIO_VidSetPinValue( copy_PORT, copy_u8PIN,HIGH);
	  }


}




