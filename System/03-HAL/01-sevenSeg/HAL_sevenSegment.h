/*********************************************************************************/
/* Author    : Bassam                                                       */
/* Version   : V01                                                           */
/* Date      : 5 JUN 2022                                                    */
/*********************************************************************************/

#ifndef HAL_SEVEN_SEGMENT_H
#define HAL_SEVEN_SEGMENT_H

#define CATHODE 0
#define ANODE   1

void seven_seg_void_init(u8 copy_PORT, u8 copy_type);
void seven_seg_void_dispaly(u8 copy_PORT, u8 copy_u8Value );


#endif