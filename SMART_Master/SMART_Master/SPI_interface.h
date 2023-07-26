
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/* ################################# Macros ############################### */
//SPCR register
#define SPR0		0		// SPI Clock Rate Select 1 and 0
#define SPR1		1
#define CPHA		2		// Clock Phase
#define CPOL		3		// Clock Polarity
#define MSTR		4		// Master/Slave Select
#define DORD		5		// Data Order
#define SPE			6		// SPI Enable
#define SPIE		7		// SPI Interrupt Enable

//SPSR register
#define SPI2X		0		// Double SPI Speed Bit
#define WCOL		6		// Write COLlision Flag
#define SPIF		7		// SPI Interrupt Flag

//SPI pinout
#define SPI_PORT		'B'
#define MOSI_PIN		 5
#define MISO_PIN		 6
#define SS_PIN			 4
#define SCK_PIN			 7

/* ################################# Includes ############################### */
#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"
#define F_CPU  8000000UL
#include "util/delay.h"

/* ################################## prototypes ###############################*/
/*
FUNCRION NAME        : SPI_vInit
FUNCTION DESCRIPTION : initializes SPI for the micro controller as slave or master according to the chosen option in config
FUNCTION INPUT       : void
FUNCTION RETURN      : void
*/
void SPI_vInit(void);

/*
FUNCRION NAME        : SPI_u8Tranceiver
FUNCTION DESCRIPTION : sends or receives data according to the type of micro controller
FUNCTION INPUT       : Copy_u8Data: data to be sent to slave
FUNCTION RETURN      : returns data the master received from the slave 
*/
uint8 SPI_u8Tranceiver(uint8 Copy_u8Data);

/*
FUNCRION NAME        : SPI_vMasterSendString
FUNCTION DESCRIPTION : sends a string in case of  the master
FUNCTION INPUT       : Copy_u8StringPointer: pointer to the first character of the string
FUNCTION RETURN      : void
*/
void SPI_vMasterSendString(uint8* Copy_u8StringPointer);

#endif 