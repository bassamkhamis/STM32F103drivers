/*********************************************************************************/
/* Author    : shrief                                                      */
/* Version   : V01                                                           */
/* Date      : 11 MAY 2022                                                    */
/*********************************************************************************/

#ifndef STEPPER_HAL_H
#define STEPPER_HAL_H


void STEPPER_void_init(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir);
void STEPPER_FORWARD(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir,u32 delay_time);
void STEPPER_REVERSE(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir,u32 delay_time);
void STEPPER_stop(u8 copy_PORT_step, u8 copy_u8PIN_step, u8 copy_PORT_dir, u8 copy_u8PIN_dir);

#endif
