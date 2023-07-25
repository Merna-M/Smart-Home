 #include "TMR1_interface.h"

/*************************************************************************************************************************************/
void (*GP_TMR1_CAPT)(void)=NULL;
/*************************************************************************************************************************************/
void TMR1_SetCallBack(void(*ptr)(void))
{
	GP_TMR1_CAPT = ptr;
}
/*************************************************************************************************************************************/

void TMR1_vInit(void)
{
	#if defined NORMAL_MODE
	//set normal mode WGM13:0 = 0000
	TCCR1A = 0;
	//set prescaler /8
	SET_BIT(TCCR1B,CS11);
	//set the noise canceler of ICU
	SET_BIT(TCCR1B,ICNC1);
	GIE_EnableInterrupt();
	
	#elif defined PWM_PHASE_CORRECT_8BIT
	//set PWM, Phase Correct, 8-bit, WGM13:0 = 0001
	SET_BIT(TCCR1A,WGM10);
	
	//Enable the Interrupt bit for ICU 
	SET_BIT(TIMSK,TICIE1);
	
	#elif defined PWM_PHASE_CORRECT_9BIT
	//set PWM, Phase Correct, 9-bit WGM13:0 = 0010
	SET_BIT(TCCR1A,WGM11);
	
	#elif defined PWM_PHASE_CORRECT_10BIT
	//set PWM, Phase Correct, 10-bit WGM13:0 = 0011
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	
	#elif defined CTC_MODE_COMP
	//set CTC mode (top = OCR1A) WGM13:0 = 0100
	SET_BIT(TCCR1B,WGM12);
	
	#elif defined FAST_PWM_8BIT
	//set Fast PWM, 8-bit, WGM13:0 = 0101
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM10);
	
	#elif defined FAST_PWM_9BIT
	//set Fast PWM, 9-bit WGM13:0 = 0110
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	
	#elif defined FAST_PWM_10BIT
	//set Fast PWM, 10-bit WGM13:0 = 0111
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1A,WGM10);
	
	#elif defined PWM_PHASE_FREQ_CORRECT_ICR
	//set PWM, Phase and Frequency Correct (top = ICR1) WGM13:0 = 1000
	SET_BIT(TCCR1B,WGM13);
	
	#elif defined PWM_PHASE_FREQ_CORRECT_CMP
	//set PWM, Phase and Frequency Correct (top = OCR1A) WGM13:0 = 1001
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1A,WGM10);
	
	#elif defined PWM_PHASE_CORRECT_MODE_ICR
	//set PWM, Phase Correct (top=ICR1) WGM13:0 = 1010
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1A,WGM11);
	
	#elif defined PWM_PHASE_CORRECT_MODE_CMP
	//set PWM, Phase Correct (top=OCR1A)  WGM13:0 = 1011
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1A,WGM10);
	
	#elif defined CTC_MODE_ICR
	//set CTC mode (top = ICR1) WGM13:0 = 1100
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	
	#elif defined FAST_PWM_MODE_ICR
	//set OCR1A as an output
	DIO_vSetPinDir(TMR1_PORT,TMR1_OCR1A_PIN,PIN_OUTPUT);
	//set Fast PWM (top = ICR1) WGM13:0 = 1110
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	
	TMR1_vSetOCR1Value(1000); // initial value (for the servo it will be at -90 (0 deg))
	ICR1 = 19999 ; // 20000 will be the overflow step
	
	// prescale /8
	SET_BIT(TCCR1B,CS11);
	
	//Clear OC1A on compare match when up-counting. Set OC1A on compare match when downcounting
	SET_BIT(TCCR1A,COM1A1);	
	
	#elif defined FAST_PWM_MODE_CMP
	//set Fast PWM (top = OCR1A) WGM13:0 = 1111
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1A,WGM10);
	
	#endif
}
/*************************************************************************************************************************************/
void TMR1_vSetOCR1Value(uint16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}
/*************************************************************************************************************************************/

uint16 TMR1_u16ICREdgeChange(void)
{
	uint16 LOC_ReturnValue;
	//wait for the selected edge change
	while(READ_BIT(TIFR,ICF1)==0);
	LOC_ReturnValue=ICR1;
	//logic 1 to clear the flag
	SET_BIT(TIFR,ICF1);
	return LOC_ReturnValue;
}
/*************************************************************************************************************************************/

void TMR1_vICUEdgeSelect(uint8 Copy_u8EdgeSelect)
{
	if(Copy_u8EdgeSelect == FALL_EDGE)
	{
		//clear edge select for falling edge
		CLR_BIT(TCCR1B,ICES1);
	}
	else if(Copy_u8EdgeSelect == RISE_EDGE)
	{
		//set edge select for rising edge
		SET_BIT(TCCR1B,ICES1);
	}
}

/*************************************************************************************************************************************/
void __vector_6()__attribute__((signal)) ;
void __vector_6()
{
	if(GP_TMR1_CAPT != NULL)
	{
		GP_TMR1_CAPT();
	}
}