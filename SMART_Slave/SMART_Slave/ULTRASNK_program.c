#include "ULTRASNK_interface.h"

void ULTRASNK_vInit(void)
{
	// set the trigger pin as an output
	DIO_vSetPinDir(ULTRASNK_PORT,TRIGGER,PIN_OUTPUT);
	TMR1_vInit();
}

static void ULTRASNK_vSendTrigger(void)
{
	DIO_vWritePin(ULTRASNK_PORT,TRIGGER,HIGH);
	_delay_us(50);
	DIO_vWritePin(ULTRASNK_PORT,TRIGGER,LOW);
}

uint16 ULTRASNK_u8MeasureDistance(void)
{
	uint16 LOC_FirstChange,LOC_SecondChange;
	uint16 Return_distance=0;
	
	ULTRASNK_vSendTrigger();
	//capture a rising edge
	TMR1_vICUEdgeSelect(RISE_EDGE);
	//get ICR1 value after capturing a rising edge
	LOC_FirstChange = TMR1_u16ICREdgeChange();
	
	//capture a falling edge
	TMR1_vICUEdgeSelect(FALL_EDGE);
	//get ICR1 value after capturing a falling edge
	LOC_SecondChange = TMR1_u16ICREdgeChange(); 
		
	Return_distance = SOUND_SPEED*(LOC_SecondChange-LOC_FirstChange)/(1000000*2);
	return Return_distance;
}