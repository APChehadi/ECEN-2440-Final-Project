/*
 * rtc.h
 *
 *  Created on: Nov 27, 2019
 *      Author: Adam Chehadi
 */

#ifndef RTC_H_
#define RTC_H_

uint8_t BSD_hour_24;
uint8_t BSD_min;
uint8_t BSD_current_min;

uint8_t BSD_MSD_hour_24;
uint8_t BSD_LSD_hour_24;

uint8_t BSD_MSD_min;
uint8_t BSD_LSD_min;

void config_rtc(void);

void RTC_C_IRQHandler(void);

//uint16_t *t_hour;

#endif /* RTC_H_ */
