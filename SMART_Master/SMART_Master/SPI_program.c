#include "SPI_interface.h"

void SPI_vInit(void)
{
	#if defined SPI_MASTER_MC
	//set MOSI,SS,SCK as outputs
	DIO_vSetPinDir(SPI_PORT,MOSI_PIN,PIN_OUTPUT);
	DIO_vSetPinDir(SPI_PORT,SS_PIN,PIN_OUTPUT);
	DIO_vSetPinDir(SPI_PORT,SCK_PIN,PIN_OUTPUT);
	//set MISO pin as input
	DIO_vSetPinDir(SPI_PORT,MISO_PIN,PIN_INPUT);
	//Enable Master mode
	SET_BIT(SPCR,MSTR);
	//set clk/16
	SET_BIT(SPCR,SPR0);
	//Enable SPI
	SET_BIT(SPCR,SPE);
	DIO_vWritePin(SPI_PORT,SS_PIN,HIGH);
	#elif defined SPI_SLAVE_MC
	//set MISO as output
	DIO_vSetPinDir(SPI_PORT,MISO_PIN,PIN_OUTPUT);
	//set MOSI,SS,SCK as inputs
	DIO_vSetPinDir(SPI_PORT,MOSI_PIN,PIN_INPUT);
	DIO_vSetPinDir(SPI_PORT,SS_PIN,PIN_INPUT);
	DIO_vSetPinDir(SPI_PORT,SCK_PIN,PIN_INPUT);
	//Enable SPI
	SET_BIT(SPCR,SPE);
	//MSTR default value =0(slave select)
	#endif
}

uint8 SPI_u8Tranceiver(uint8 Copy_u8Data)
{
	#if defined SPI_MASTER_MC
	//send 0 to activate the slave
	DIO_vWritePin(SPI_PORT,SS_PIN,LOW);
	#endif
	//put data at the SPI data register
	SPDR = Copy_u8Data;
	while(READ_BIT(SPSR,SPIF)==0);
	return SPDR;
}

void SPI_vMasterSendString(uint8* Copy_u8StringPointer)
{
	uint8 LOC_receive;
	while(*Copy_u8StringPointer != '\0')
	{
		LOC_receive = SPI_u8Tranceiver(*Copy_u8StringPointer);
		Copy_u8StringPointer++;
		_delay_ms(200);
	}
}