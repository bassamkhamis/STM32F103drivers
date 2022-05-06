/*
Auther :bassam
Date Feb 5 2022

*/

#include <stdint.h>
#define STACK_POINTER 0x20001000

extern int main(void);
extern uint32_t _E_text;
extern uint32_t _S_DATA;
extern uint32_t _E_DATA;
extern uint32_t _S_bss;
extern uint32_t _E_bss;
extern uint32_t _stack_top;

void rest_handler(void);
void Default_handler(void);

void rest_handler(void){
    /*copy data section from flash to Sram*/
	uint32_t Data_size = (uint8_t *)&_E_DATA - (uint8_t *)&_S_DATA;
	uint8_t * p_src = (uint8_t *)&_E_text;
	uint8_t * p_dst = (uint8_t *)&_S_DATA;
	for(int i=0; i<Data_size; i++){
		
		*((uint8_t *)p_dst++) = *((uint8_t *)p_src++);
	}
	/* init .bss with zero*/
	uint32_t bss_size = (uint8_t *)&_E_bss - (uint8_t *)&_S_bss;
	p_dst = (uint8_t *)&_S_bss;
	for(int i=0; i<bss_size; i++){
	*((uint8_t *)p_dst++) = *(uint8_t *)0 ;	
		
	}
	
 main();
}
void Default_handler(void){
	rest_handler();
	
}
void NMI_handler(void)__attribute__((weak, alias("Default_handler")));
void H_fault_handler(void)__attribute__((weak, alias("Default_handler")));
void MM_fault_handler(void)__attribute__((weak, alias("Default_handler")));
void Bus_fault_handler(void)__attribute__((weak, alias("Default_handler")));
void Usage_fault_handler(void)__attribute__((weak, alias("Default_handler")));
void TIM_handler(void)__attribute__((weak, alias("Default_handler")));


uint32_t vectors[]__attribute__((section(".vectors"))) ={
	
	(uint32_t) &_stack_top,
	(uint32_t) &rest_handler,
	(uint32_t) &NMI_handler,
	(uint32_t) &H_fault_handler,
	(uint32_t) &MM_fault_handler,
	(uint32_t) &Bus_fault_handler,
	(uint32_t) &Usage_fault_handler,
	(uint32_t) &TIM_handler
	
};



