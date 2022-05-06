/*********************************************************************************/
/* Author    : Bassam                                                       */
/* Version   : V01                                                           */
/* Date      : 5 JUN 2022                                                    */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "HAL_sevenSegment.h"

u8 num_7seg_cathode[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
u8 num_7seg_anode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void seven_seg_void_init(u8 copy_PORT, u8 copy_type){
		   switch(copy_PORT){
		   
		   case GPIOA:
					
			              MGPIO_VidSetPinDirection(GPIOA , PIN0 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN1 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN2 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN3 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN4 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN5 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN6 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN7 , OUTPUT_SPEED_2MHZ_PP);
						  break;

					
							

		   
		   
		        
		   
		   
		   case GPIOB:
			              MGPIO_VidSetPinDirection(GPIOB , PIN0 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN1 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN2 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN3 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN4 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN5 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOA , PIN6 , OUTPUT_SPEED_2MHZ_PP);
			              MGPIO_VidSetPinDirection(GPIOB , PIN7 , OUTPUT_SPEED_2MHZ_PP);
						  break;
						  
			default :
                         break;			
	
	
	
   }

}
void seven_seg_void_dispaly(u8 copy_PORT, u8 copy_u8Value ){
	
	
	   switch(copy_PORT){
		   
		   case GPIOA:
                    MGPIO_voidWrite8PinValue( copy_PORT , num_7seg_anode[copy_u8Value]);
		   
		            break;
		   
		   
		   case GPIOB:
		   
		             MGPIO_voidWrite8PinValue( copy_PORT , num_7seg_anode[copy_u8Value]);
		   
		             break;
		   
		   
		default :
			     break;			
	
		   
		   
		   
		   
		   
		   
		   
		   
	   }
	
	
}

