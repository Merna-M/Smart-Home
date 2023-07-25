/*
 * SMART_Slave.c
 *
 * Created: 7/23/2023 1:04:42 PM
 *  Author: MERNA
 */ 

/** Libraries **/
#include "STD_types.h"
#define F_CPU 8000000UL
#include "util/delay.h"

/** MCAL **/
#include "SPI_interface.h"
#include "TMR0_interface.h"

/** HAL **/
#include "LED_interface.h"
#include "ULTRASNK_interface.h"
#include "MOTOR_interface.h"


uint8 TMR0_counter = 0;
uint16 Distance;

void TMR0_ISR(void)
{
	TMR0_counter++;
	if(TMR0_counter>=33)
	{
		TMR0_counter=0;
		Distance = ULTRASNK_u8MeasureDistance(); 
		if(Distance<20)
		{
			LED_vSwitchON('A',1);
			LED_vSwitchOFF('A',2);
		}
		else
		{
			LED_vSwitchOFF('A',1);
			LED_vSwitchON('A',2);
		}
	}
}
int main(void)
{
	uint8 SPI_Receive;
	
	/* ROOMs Initialization */
	LED_vInit('D',0);
	LED_vInit('D',1);
	LED_vInit('D',2);
	/* Fans Initialization */
	MOTOR_vInit('C',0,1);
	MOTOR_vInit('C',2,3);
	
	ULTRASNK_vInit();
	LED_vInit('A',2);
	LED_vInit('A',1);
	
	SPI_vInit();
	TMR0_vInit();
	TMR0_COMP_SetCallBack(TMR0_ISR);
	
	
    while(1)
    {
		
        SPI_Receive = SPI_u8Tranceiver('a');
		if(SPI_Receive == '1') // ROOM1
		{
			SPI_Receive = SPI_u8Tranceiver('a');
			if(SPI_Receive == 'N')//trun ON
			{
				LED_vSwitchON('D',0);
			}	
			else if(SPI_Receive == 'F')
			{
				LED_vSwitchOFF('D',0);
			}
		}
		else if(SPI_Receive == '2')//ROOM2	
		{
			SPI_Receive = SPI_u8Tranceiver('a');
			if(SPI_Receive == 'N')//trun ON
			{
				LED_vSwitchON('D',1);
			}
			else if(SPI_Receive == 'F')
			{
				LED_vSwitchOFF('D',1);
			}
		}		
		else if(SPI_Receive == '3')//ROOM3
		{
			SPI_Receive = SPI_u8Tranceiver('a');
			if(SPI_Receive == 'N')//trun ON
			{
				LED_vSwitchON('D',2);
			}
			else if(SPI_Receive == 'F')
			{
				LED_vSwitchOFF('D',3);
			}
		}
		else if(SPI_Receive == '4')
		{
			SPI_Receive = SPI_u8Tranceiver('a');
			if(SPI_Receive == 'N')//trun ON
			{
				MOTOR_vRotate('C',0,1,MOTOR_ROTATE_LEFT);
			}
			else if(SPI_Receive == 'F')
			{
				MOTOR_vRotate('C',0,1,MOTOR_STOPS);
			}
		}
		else if(SPI_Receive == '5')
		{
			SPI_Receive = SPI_u8Tranceiver('a');
			if(SPI_Receive == 'N')//trun ON
			{
				MOTOR_vRotate('C',2,3,MOTOR_ROTATE_LEFT);
			}
			else if(SPI_Receive == 'F')
			{
				MOTOR_vRotate('C',2,3,MOTOR_STOPS);
			}
		}
		else if(SPI_Receive == '6')
		{
			Distance = ULTRASNK_u8MeasureDistance();
			if(Distance<20)
			{
				SPI_u8Tranceiver('B');
			}
			else
			{
				SPI_u8Tranceiver('E');
			}
		}						
    }
}