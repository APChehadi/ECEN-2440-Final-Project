#include "msp.h"
#include "rtc.h"
#include <stdio.h>
#include <stdlib.h>


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	config_rtc();
	RTC_C_IRQHandler();
}
