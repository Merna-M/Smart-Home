
#ifndef _TMR1_PRIVATE_H_
#define _TMR1_PRIVATE_H_

/* flag and enable registers */
#define TIMSK		*((volatile uint8*)(0x59))
#define TIFR		*((volatile uint8*)(0x58))

/* control registers */
#define TCCR1A		*((volatile uint8*)(0x4F))
#define TCCR1B		*((volatile uint8*)(0x4E))

/* TCNT1 register */
#define TCNT1H		*((volatile uint8*)(0x4D))
#define TCNT1L		*((volatile uint8*)(0x4C))
#define TCNT1		*((volatile uint16*)(0x4C))

/* OCR1 registers */
#define OCR1AH		*((volatile uint8*)(0x4B))
#define OCR1AL		*((volatile uint8*)(0x4A))
#define OCR1A		*((volatile uint16*)(0x4A))

#define OCR1BH		*((volatile uint8*)(0x49))
#define OCR1BL		*((volatile uint8*)(0x48))
#define OCR1B		*((volatile uint16*)(0x48))

/* ICR register */
#define ICR1H		*((volatile uint8*)(0x47))
#define ICR1L		*((volatile uint8*)(0x46))
#define ICR1		*((volatile uint16*)(0x46))



#endif 