// ********************** START OF PCIRQ.H **********************
//
//
//
// This header file has the prototypes and definitions used with the
// IRQ manager routines.  The three public functions have their
// prototypes here.  All the code for the IRQ manager is found in
// PCIRQ.CPP.

#ifndef _PCIRQ_DOT_H
#define _PCIRQ_DOT_H

#include "rs232.h"

enum irq_name {  IRQ0 = 0, IRQ1, IRQ2,  IRQ3,  IRQ4,  IRQ5,  IRQ6,  IRQ7,
				 IRQ8,     IRQ9, IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15,
				 ILLEGAL_IRQ = -1 };

RS232Error  ConnectToIrq( irq_name irq,
                         void *isr_data_block,
                         void ( *isr_routine )( void *isr_data_block ) );
int DisconnectFromIRQ( enum irq_name irq );

#endif // #ifndef _PCIRQ_DOT_H

// ************************ END OF PCIRQ.H ***********************

