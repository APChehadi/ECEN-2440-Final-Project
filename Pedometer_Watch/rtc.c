/*
 * rtc.c
 *
 *  Created on: Nov 27, 2019
 *      Author: Adam Chehadi
 */

#include "msp.h"
#include "rtc.h"
#include <stdio.h>
#include <stdlib.h>


void config_rtc(void) {
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;

    RTC_C -> CTL0 = RTC_C_KEY |             /*!< RTC_C Key Value for RTC_C write access */
                   RTC_C_CTL0_TEVIE |       /*!< Real-time clock time event interrupt enable */
                   RTC_C_CTL0_TEVIFG;       /*!< Real-time clock time event interrupt flag */

    RTC_C -> CTL13 = RTC_C_CTL13_HOLD |     /*!< Real-time clock hold */
                    RTC_C_CTL13_MODE |
                    RTC_C_CTL13_BCD |       /*!< Real-time clock BCD select */
                    RTC_C_CTL13_TEV_0;      /*!< Minute changed */

    RTC_C -> YEAR = 0x2019;                          // Year = 0x2019
    RTC_C -> DATE = (0x12 << RTC_C_DATE_MON_OFS) |    // Month = 0x12 = December
           (0x08 | RTC_C_DATE_DAY_OFS);             // Day = 0x02 = 2nd
    RTC_C -> TIM1 = (0x07 << RTC_C_TIM1_DOW_OFS) |   // Day of week = 0x01 = Monday
           (0x19 << RTC_C_TIM1_HOUR_OFS);           // Hour = 0x11
    RTC_C -> TIM0 = (0x00 << RTC_C_TIM0_MIN_OFS) |   // Minute = 0x33
           (0x45 << RTC_C_TIM0_SEC_OFS);            // Seconds = 0x45

    // Start RTC calendar mode
    RTC_C -> CTL13 = RTC_C -> CTL13 & ~(RTC_C_CTL13_HOLD);

    // Lock the RTC registers
    RTC_C -> CTL0 = RTC_C -> CTL0 & ~(RTC_C_CTL0_KEY_MASK);

    // Enable global interrupt
    __enable_irq();

    NVIC->ISER[0] = 1 << ((RTC_C_IRQn) & 31);

        // Sleep on exit from ISR
        SCB -> SCR |= SCB_SCR_SLEEPONEXIT_Msk;

        __DSB();

        while (1)
        {
            // Setting the sleep deep bit
            SCB -> SCR |= (SCB_SCR_SLEEPDEEP_Msk);

            // Ensures SLEEPDEEP takes effect immediately
            __DSB();

            __sleep();

            // Clearing the sleep deep bit
            SCB -> SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);
        }
}


void RTC_C_IRQHandler(void)
{
    if (RTC_C -> CTL0 & RTC_C_CTL0_TEVIFG)
    {
        if((((RTC_C->TIM1 & (RTC_C_TIM1_HOUR_LD_MASK | RTC_C_TIM1_HOUR_HD_MASK))>>RTC_C_TIM1_HOUR_OFS) == 0x19) &&
           (((RTC_C->TIM0 & (RTC_C_TIM0_MIN_LD_MASK | RTC_C_TIM0_MIN_HD_MASK))>>RTC_C_TIM0_MIN_OFS) == 0x02) &&
           (((RTC_C->TIM0 & (RTC_C_TIM0_SEC_LD_MASK | RTC_C_TIM0_SEC_HD_MASK))>>RTC_C_TIM0_SEC_OFS) == 0x00))
        {
            P1->OUT |= BIT0;
            while(1);
        }

        P1 -> OUT ^= BIT0;

        // Unlock the RTC module and clear time event interrupt flag
        RTC_C -> CTL0 = (RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK |  RTC_C_CTL0_TEVIFG)) | RTC_C_KEY;

        // Re-lock the RTC
        RTC_C -> CTL0 = RTC_C->CTL0 & ~(RTC_C_CTL0_KEY_MASK);
    }
}
