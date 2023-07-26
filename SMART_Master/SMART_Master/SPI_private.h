
#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//SPI control register
#define SPCR	*((volatile uint8*)(0x2D))
//status register
#define SPSR	*((volatile uint8*)(0x2E))
//SPI data register
#define SPDR	*((volatile uint8*)(0x2F))



#endif 