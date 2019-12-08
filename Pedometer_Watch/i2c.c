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

    EUSCI_B0 -> CTLW0 |= (EUSCI_B_CTLW0_MODE_3 |  /*!< I2C mode */
                        EUSCI_B_CTLW0_MST    |  /*!< Master mode select */
                        EUSCI_B_CTLW0_UCSSEL_3);    /*!< SMCLK */

    EUSCI_B0 -> BRW = 30;   // Setting clock prescalar for 100 kHz

    // Clear UCSWRST in software
    EUSCI_B0 -> CTLW0 &= ~(EUSCI_B_CTLW0_SWRST);

    // Enable interrupts
    EUSCI_B0 -> IFG = 0;    /*!< eUSCI_Bx Interrupt Flag Register */
}


void rx_data(uint8_t address, uint8_t register) {
    // Slave transmitter mode is entered when the slave address transmitted by the master is identical to its own
    // Master needs to act as transmitter to send the address so it can enter Slave Transmitter Mode / Master Receive Mode
    EUSCI_B0 -> CTLW0 |= EUSCI_B_CTLW0_TR;

    // Write desired slave address
    EUSCI_B0 -> I2CSA = address;

    // Clear the UCTR for receiver mode
    EUSCI_B0 -> CTLW0 &= ~(EUSCI_B_CTLW0_TR);

    // Set UCTXSTT to generate a START condition
    EUSCI_B0 -> CTLW0 |= EUSCI_B_CTLW0_TXSTT;

    // Read UCBxRXBUF
    uint8_t rx_register_buffer_data = 0xFF;
    rx_register_buffer_data = EUSCI_B0 -> RXBUF;
}
