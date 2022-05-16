/*
 * HX7111_force_sensor.h
 *
 *  Created on: May 13, 2022
 *      Author: bassam
 */

#ifndef HX7111_FORCE_SENSOR_H_
#define HX7111_FORCE_SENSOR_H_
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "STK_interface.h"




unsigned long ReadCount(void);
//void HAL_voidcalibrate(void);
int HAL_intGetForceVal(void);

#endif /* HX7111_FORCE_SENSOR_H_ */
