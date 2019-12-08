/*
 * i2c.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Adam Chehadi
 */

#include "msp.h"
#include "i2c.h"
#include <stdio.h>
#include <stdlib.h>


void init_i2c(void) {
    // Initialize eUSCI_B registers with setting the UCSWRST bit
    EUSCI_B0 -> CTLW0 |= EUSCI_B_CTLW0_SWRST;   /*!< Software reset enable */

    // Configure ports
    P6->SEL0 |= (BIT4 | BIT5);
    P6->SEL1 &= ~(BIT4 | BIT5);

    // Clear UCSWRST in software
    EUSCI_B0 -> CTLW0 &= ~(EUSCI_B_CTLW0_SWRST);

    // Enable interrupts
    EUSCI_B0 -> IFG = 0;    /*!< eUSCI_Bx Interrupt Flag Register */
}
