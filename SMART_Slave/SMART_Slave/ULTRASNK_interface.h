
#ifndef _ULTRASNK_INTERFACE_H_
#define _ULTRASNK_INTERFACE_H_

/* ############################# Macros #############################*/
/* TIFR Register */
#define ICF1	5

#define SOUND_SPEED		34600



/* ############################# Includes ############################*/
#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_interface.h"
#include "ULTRASNK_config.h"
#include "TMR1_interface.h"
#define F_CPU 8000000UL
#include "util/delay.h"


/* ############################# Prototypes #################################*/

/*
FUNCTION NAME        : ULTRASNK_vInit
FUNCTION DESCRIPTION : Initializes the ultra sonic by initializing the trigger pin as an output 
FUNCTION INPUTS	     : void
FUNCTION RETURN      : void
*/
void ULTRASNK_vInit(void);

/*
FUNCTION NAME        : ULTRASNK_vSendTrigger
FUNCTION DESCRIPTION : sends a trigger to the ultrasonic to send a sound signal
FUNCTION INPUTS	     : void
FUNCTION RETURN      : void
*/
static void ULTRASNK_vSendTrigger(void);

/*
FUNCTION NAME        : ULTRASNK_u8MeasureDistance
FUNCTION DESCRIPTION : measures the distance by measuring the time the sound signal to hit the obstacle and return
FUNCTION INPUTS	     : void
FUNCTION RETURN      : returns the distance in cm
*/
uint16 ULTRASNK_u8MeasureDistance(void);


#endif 