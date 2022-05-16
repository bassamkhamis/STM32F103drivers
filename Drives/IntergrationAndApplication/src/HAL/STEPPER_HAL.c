/*********************************************************************************/
/* Author    : shrief ashraf                                                      */
/* Version   : V01                                                           */
/* Date      : 5 MAY 2022                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STEPPER_HAL.h"
#include "STK_interface.h"

void STEPPER_void_init(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir)
{
	
	switch(copy_PORT_step){
		   
		   case GPIOA:   MGPIO_VidSetPinDirection(copy_PORT_step,copy_u8PIN_step, OUTPUT_SPEED_10MHZ_PP);

					     break;
		   case GPIOB:    MGPIO_VidSetPinDirection(copy_PORT_step,copy_u8PIN_step, OUTPUT_SPEED_10MHZ_PP);

					     break;			  			  
		    case GPIOC:  MGPIO_VidSetPinDirection(copy_PORT_step,copy_u8PIN_step, OUTPUT_SPEED_10MHZ_PP);

				             break;			  			  
			default :
                         break;
	
        }

       switch(copy_PORT_dir){
		   
		   case GPIOA:   MGPIO_VidSetPinDirection(copy_PORT_dir,copy_u8PIN_dir, OUTPUT_SPEED_10MHZ_PP);

					     break;

		   case GPIOB:    MGPIO_VidSetPinDirection(copy_PORT_dir,copy_u8PIN_dir, OUTPUT_SPEED_10MHZ_PP);

					     break;
						  			  
		    case GPIOC:  MGPIO_VidSetPinDirection(copy_PORT_dir,copy_u8PIN_dir, OUTPUT_SPEED_10MHZ_PP);

				             break;			  
						  
			default :
                         break;
	
        }
}

void STEPPER_FORWARD(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir,u32 delay_time)
{
	MGPIO_VidSetPinValue( copy_PORT_dir, copy_u8PIN_dir,HIGH);
        MGPIO_VidSetPinValue( copy_PORT_step, copy_u8PIN_step,HIGH);
        MSTK_voidSetBusyWait(delay_time);
        MGPIO_VidSetPinValue( copy_PORT_step, copy_u8PIN_step,LOW);
        MSTK_voidSetBusyWait(delay_time);
}

void STEPPER_REVERSE(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir,u32 delay_time)
{
	MGPIO_VidSetPinValue( copy_PORT_dir, copy_u8PIN_dir,LOW);
        MGPIO_VidSetPinValue( copy_PORT_step, copy_u8PIN_step,HIGH);
        MSTK_voidSetBusyWait(delay_time);
        MGPIO_VidSetPinValue( copy_PORT_step, copy_u8PIN_step,LOW);
        MSTK_voidSetBusyWait(delay_time);
}
void STEPPER_stop(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir)
{
	MGPIO_VidSetPinValue( copy_PORT_dir, copy_u8PIN_dir,LOW);
        MGPIO_VidSetPinValue( copy_PORT_step, copy_u8PIN_step,LOW);
}
