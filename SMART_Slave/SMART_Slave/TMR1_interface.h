
#ifndef _TMR1_INTERFACE_H_
#define _TMR1_INTERFACE_H_

/*############################ Macros ############################*/

/* TIMSK Register */
#define TOIE1	2
#define OCIE1B	3
#define OCIE1A	4
#define TICIE1	5

/* TIFR Register */
#define TOV1	2
#define OCF1B	3
#define OCF1A	4
#define ICF1	5

/* TCCR1A Register */
#define WGM10	0
#define WGM11	1
#define FOC1B	2
#define FOC1A	3
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7

/* TCCR1B Register */
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4

#define ICES1	6 //input capture edge select(falling or rising)
#define ICNC1	7 //input capture noise canceler

/* Timer 1 Pins */
#define TMR1_PORT			'D'
#define TMR1_OCR1A_PIN		 5
#define TMR1_OCR1B_PIN		 4
#define TMR1_ICP1_PIN		 6

/* ICU Edge select choices */
#define FALL_EDGE			0
#define RISE_EDGE			1


/* ############################# INCLUDES #################################*/
#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_interface.h"
#include "TMR1_private.h"
#include "TMR1_config.h"
#include "TMR1_interface.h"


/*############################# Prototypes ###################################*/
void TMR1_SetCallBack(void(*ptr)(void));
/*
FUNCTION NAME        : TMR1_vInit
FUNCTION DESCRIPTION : initializes timer1 according to the mode defined in config
FUNCTION INPUTS      : void
FUNCTION RETURN      : void
*/
void TMR1_vInit(void);

/*
FUNCTION NAME        : TMR1_vSetOCR1Value
FUNCTION DESCRIPTION : set OCR1A to some certain value
FUNCTION INPUTS      : Copy_u16Value: value to be put in the OCR1A register
FUNCTION RETURN      : void
*/
void TMR1_vSetOCR1Value(uint16 Copy_u16Value);

/*
FUNCTION NAME        : TMR1_u16ICREdgeChange
FUNCTION DESCRIPTION : returns the ICR1 value when the selected edge change occurs
FUNCTION INPUTS      : void
FUNCTION RETURN      : returns the value of ICR1
*/
uint16 TMR1_u16ICREdgeChange(void);

/*
FUNCTION NAME        : TMR1_vICUEdgeSelect
FUNCTION DESCRIPTION : used to select an edge , a rising or a falling edge
FUNCTION INPUTS      : Copy_u8EdgeSelect: selected edge
FUNCTION RETURN      : void
*/
void TMR1_vICUEdgeSelect(uint8 Copy_u8EdgeSelect);

#endif 