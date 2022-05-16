//*********************************************************************************/
/* Author    : Embedded system Sub team                                          */
/* Version   : V01                                                              */
/* Date      : 14 May 2020                                                     */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"


// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"
/******** includes Section **********/
#include "STD_TYPES.h"
#include "math.h"
#include "MCAL/RCC_interface.h"
#include "MCAL/DIO_interface.h"
#include "MCAL/USART_interface.h"
#include "MCAL/STK_interface.h"
#include "HAL/HX7111_force_sensor.h"
#include "HAL/STEPPER_HAL.h"
#include "MCAL/ADC_interface.h"
/*************************************/

//-----------------global variables -------
float force;
float DeltaLength;
float Area = 125;   //mm2
float length = 10;   // meter
float Stress;
float Strain;
u8 X_axis[100];
u8 Y_axis[100];
int Gcount=0;
char breakpoint = 0;
//------------------------------
#define DELTA(x)  ADC_u16ReadChannelPoll(x)*(70.0/4096) // mm
//------------------Macros---------
#define START_M             PIN7               // On or high (Toggle)     GPIOA
#define MOTOR_UP            PIN4               // normal push button      GPIOA
#define MOTOR_DOWN          PIN3               // normal push button      GPIOA
#define START_PROCESS       PIN5               //Toggle                   GPIOA
#define TOGGLE              PIN1               // tension or compression  GPIOA
//-----------------------------
#define PISTON_UP      PIN12
#define PISTON_DOWN    PIN13
void switches(void)
{

	MGPIO_VidSetPinDirection(GPIOA,START_M,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,MOTOR_UP,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,MOTOR_DOWN,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,START_PROCESS,INPUT_FLOATING);
	MGPIO_VidSetPinDirection(GPIOA,TOGGLE,INPUT_FLOATING);

	MGPIO_VidSetPinDirection(GPIOB,PISTON_UP,OUTPUT_SPEED_10MHZ_PP); //for  pump Up
	MGPIO_VidSetPinDirection(GPIOB,PISTON_DOWN,OUTPUT_SPEED_10MHZ_PP);//for pump down

}

void adjustmotor()
{
	if(MGPIO_u8GetPinValue ( GPIOA , MOTOR_UP))
	{
		STEPPER_FORWARD(GPIOB, PIN14, GPIOB, PIN15,1000); //range time delay from 50 to 1000
	}
	else if(MGPIO_u8GetPinValue ( GPIOA , MOTOR_DOWN))
	{
		STEPPER_REVERSE(GPIOB, PIN14, GPIOB, PIN15,1000);
	}
	else
	{
		STEPPER_stop(GPIOB, PIN14, GPIOB, PIN15);
	}
}

void Tension(void)
{    	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, HIGH);
	force = HAL_intGetForceVal();
	while(force>0 && MGPIO_u8GetPinValue(GPIOA,TOGGLE))
	{

	force = HAL_intGetForceVal();
	DeltaLength = DELTA(0);
	Stress  = force / Area;  //stress eqn
	Strain  = DeltaLength / length; // srain eqn
	X_axis[Gcount] = (char) Stress * 10;             //i.e. 1.4*10 = 14
	Y_axis[Gcount] = (char) Strain * 10;
	Gcount++;
	}
	for(int i=0; i<=Gcount; i++){
	MUSART1_voidTransmit(&X_axis[i],1);
	MUSART1_voidTransmit(&Y_axis[i],1);
	}
	Gcount =0 ;
	breakpoint = 1;
	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);

}

void Compression ()
{   MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, HIGH);
	force = HAL_intGetForceVal();
	while(force>0 && MGPIO_u8GetPinValue(GPIOA,TOGGLE))
	{
	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, HIGH);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
	force = HAL_intGetForceVal();
	DeltaLength = DELTA(0);
	Stress  = force / Area;  //stress eqn
	Strain  = DeltaLength / length; // srain eqn
	X_axis[Gcount] = (char) Stress * 10;             //i.e. 1.4*10 = 14
	Y_axis[Gcount] = (char) Strain * 10;
	Gcount++;
	}
	for(int i=0; i<=Gcount; i++){
	MUSART1_voidTransmit(&X_axis[i],1);
	MUSART1_voidTransmit(&Y_axis[i],1);
	}
	Gcount =0 ;
	breakpoint = 1;
	MGPIO_VidSetPinValue(GPIOB, PISTON_UP, LOW);
	MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN, LOW);
}
int main(int argc, char* argv[])
{

	// init preigherals and clocks

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);  // clocks for port A
	RCC_voidEnableClock(RCC_APB2,3);  // clocks for port B
	RCC_voidEnableClock(RCC_APB2,9);  // clocks for ADC1
	RCC_voidEnableClock(RCC_APB2,14); // clocks for UART1
	MSTK_voidInit();
	ADC_VoidInit();
	MUSART1_voidInit();
	//--------------------------------
	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_VidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_VidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);
	STEPPER_void_init(GPIOB,PIN14,GPIOB,PIN15);
	switches(); //Init swithes
while(1)
{
	if (MGPIO_u8GetPinValue(GPIOA,START_M) && breakpoint==0){

		adjustmotor();
		if(MGPIO_u8GetPinValue(GPIOA,START_PROCESS))
		{
			if(MGPIO_u8GetPinValue(GPIOA,TOGGLE))   // if high
			{
				Compression();
			}
			else if(!MGPIO_u8GetPinValue(GPIOA,TOGGLE)) //if low
			{
				Tension();
			}

		}
		else {

			MGPIO_VidSetPinValue(GPIOB, PISTON_DOWN,LOW);
			MGPIO_VidSetPinValue(GPIOB, PISTON_UP,LOW);
		}


	}

}

}

// -----------------------------------------

#pragma GCC diagnostic pop
