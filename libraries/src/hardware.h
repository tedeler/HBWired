/*
 * hardware.h
 *
 *  Created on: 23.05.2018
 *      Author: loetmeister.de
 */

#ifndef hardware_h
#define hardware_h

/* Start Boot Program section and RAM address start */
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
// Boot Size 2048 words
#define BOOTSTART (0x3800)
#endif


#if defined(__AVR_ATmega168__)
#define RAMSTART (0x100)
#define NRWWSTART (0x3800)
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define RAMSTART (0x100)
#define NRWWSTART (0x7000)
#elif defined (__AVR_ATmega644P__)
#define RAMSTART (0x100)
#define NRWWSTART (0xE000)
#elif defined(__AVR_ATtiny84__)
#define RAMSTART (0x100)
#define NRWWSTART (0x0000)
#elif defined(__AVR_ATmega1280__)
#define RAMSTART (0x200)
#define NRWWSTART (0xE000)
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
#define RAMSTART (0x100)
#define NRWWSTART (0x1800)
#endif


#endif /* hardware */