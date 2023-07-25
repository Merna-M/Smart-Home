#include "MOTOR_interface.h"


void MOTOR_vInit(uint8 Copy_u8MotorPort ,uint8 Copy_u8MotorPin1 , uint8 Copy_u8MotorPin2)
{
	DIO_vSetPinDir(Copy_u8MotorPort,Copy_u8MotorPin1,PIN_OUTPUT);
	DIO_vSetPinDir(Copy_u8MotorPort,Copy_u8MotorPin2,PIN_OUTPUT);
}


void MOTOR_vRotate(uint8 Copy_u8MotorPort ,uint8 Copy_u8MotorPin1 , uint8 Copy_u8MotorPin2 , uint8 Copy_u8Direction)
{
	if(Copy_u8Direction == MOTOR_ROTATE_LEFT)
	{
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin2,LOW);
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin1,HIGH);
	}
	else if(Copy_u8Direction == MOTOR_ROTATE_RIGHT)
	{
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin1,LOW);
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin2,HIGH);
	}
	else if(Copy_u8Direction == MOTOR_STOPS)
	{
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin1,LOW);
		DIO_vWritePin(Copy_u8MotorPort,Copy_u8MotorPin2,LOW);
	}
}