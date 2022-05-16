/*
 * HX7111_force_sensor.c
 *
 *  Created on: May 13, 2022
 *      Author: bassam
 */
#include "HX7111_force_sensor.h"
#define CLK    PIN6
#define DATA   PIN7



int sample=0;
float val=0;
int count=0;


int HAL_intGetForceVal(void){
	int w;
	count = ReadCount();
	w=(((count-sample)/val)-2*((count-sample)/val));
	return w;
}




unsigned long ReadCount(void){

	unsigned long Count;
	char i;


	MGPIO_VidSetPinDirection(GPIOB,DATA,OUTPUT_SPEED_10MHZ_PP);
	MGPIO_VidSetPinValue(GPIOB,DATA,HIGH);
	//DDRD |= (1<<DATA);   // as output dout
	//PORTD |= (1<<DATA);
	//ADDO=1;

	MGPIO_VidSetPinDirection(GPIOB,CLK,OUTPUT_SPEED_10MHZ_PP);
	MGPIO_VidSetPinValue(GPIOB,CLK,LOW);
	//PORTD &= ~(1<<CLK);
	//ADSK=0;
	MGPIO_VidSetPinDirection(GPIOB,DATA,INPUT_FLOATING);
	//DDRD &= ~(1<<DATA);   // as input dout

	Count=0;

	while(MGPIO_u8GetPinValue(GPIOB,DATA)){}
	// while(ADDO);
	for (i=0;i<24;i++){
		MGPIO_VidSetPinValue(GPIOB,CLK,HIGH);
		MSTK_voidSetBusyWait(1);
		// PORTD |= (1<<CLK);
		// ADSK=1;
		Count=Count<<1;

		MGPIO_VidSetPinValue(GPIOB,CLK,LOW);
		MSTK_voidSetBusyWait(1);
		//PORTD &= ~(1<<CLK);
		// ADSK=0;
		if(MGPIO_u8GetPinValue(GPIOB,DATA)  ) Count++;
	}

	MGPIO_VidSetPinValue(GPIOB,CLK,HIGH);
	MSTK_voidSetBusyWait(1);
	//PORTD |= (1<<CLK);
	// ADSK=1;
	Count=Count^0x800000;
	MGPIO_VidSetPinValue(GPIOB,CLK,LOW);
	MSTK_voidSetBusyWait(1);
	// PORTD &= ~(1<<CLK);
	// ADSK=0;
	return(Count);
}

//void HAL_voidcalibrate(void)
//{
//
//	LCD_clear_screen();
//	LCD_WRITE_STRING("Calibrating...");
//	LCD_GOTO_XY(2,0);
//	LCD_WRITE_STRING("Please Wait...");
//	for(int i=0;i<500;i++)
//	{
//		count=ReadCount();
//		sample+=count;
//	}
//	sample/=500;
//	LCD_clear_screen();
//	LCD_WRITE_STRING("Put 100 g weight");
//	count=0;
//	while(count<1000)
//	{
//		count=ReadCount();
//		count=sample-count;
//	}
//	LCD_clear_screen();
//	LCD_WRITE_STRING("Please Wait....");
//	MSTK_voidSetBusyWait(2000000);
//	for(int i=0;i<500;i++)
//	{
//		count=ReadCount();
//		val+=sample-count;
//	}
//	val=val/500.0;
//	val=val/100.0; // put here your calibrating weight
//	LCD_clear_screen();
//}

