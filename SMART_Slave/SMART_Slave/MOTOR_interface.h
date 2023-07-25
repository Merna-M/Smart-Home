
#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

/* ################################ Macros ################################### */


/* L298 Motor Driver */
#define MOTOR_ROTATE_LEFT		0
#define MOTOR_ROTATE_RIGHT		1
#define MOTOR_STOPS				2



/* ################################ Includes ################################# */
#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_interface.h"



/* ################################ Prototypes ################################### */

void MOTOR_vInit(uint8 Copy_u8MotorPort ,uint8 Copy_u8MotorPin1 , uint8 Copy_u8MotorPin2);

void MOTOR_vRotate(uint8 Copy_u8MotorPort ,uint8 Copy_u8MotorPin1 , uint8 Copy_u8MotorPin2 , uint8 Copy_u8Direction);


#endif 