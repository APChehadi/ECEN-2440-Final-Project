/*
 * time.c
 *
 *  Created on: Dec 9, 2019
 *      Author: adamp
 */

#include "msp.h"
#include "time.h"
#include "rtc.h"
#include <stdio.h>
#include <stdlib.h>


void run_time(void) {
    while(1){
        if(BSD_current_min != BSD_min) {
            printf("%d", BSD_min);
            BSD_current_min += 1;
        }
    }
}
