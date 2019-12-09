/*
 * imu.c
 *
 *  Created on: Dec 9, 2019
 *      Author: Adam Chehadi
 */

#include "msp.h"
#include "i2c.h"
#include "imu.h"
#include <stdio.h>
#include <stdlib.h>

#define IMU                 0x69        // 7-bit address

#define PWR_MGMT_1          0x06
#define LP_CONFIG           0x05
#define INT_PIN_CFG         0x0F
#define ACCEL_CONFIG        0x14
#define GYRO_CONFIG_1       0x14

#define VAL_1               0x01
#define VAL_2               0x40
#define VAL_3               0x02
#define VAL_4               0x38
#define VAL_5               0x38


void config_imu(void) {
    int i;
   for (i=0; i<10000;i++); // Start-up time
   printf("Connecting to ICM20948...\n");
   for(i=0; i<100000; i++);
   printf("...\n");
   for(i=0; i<100; i++);
   printf("...\n");
   for(i=0; i<100; i++);
   uint8_t whoami = read_register(IMU, 0x00); //Reads WHO_AM_I register
   printf("Who am I? This is device 0x%x.\n",whoami);

    write_register(IMU, PWR_MGMT_1, VAL_1);

    write_register(IMU, LP_CONFIG, VAL_2);

    write_register(IMU, INT_PIN_CFG, VAL_3);

    write_register(IMU, ACCEL_CONFIG, VAL_4);

    write_register(IMU, GYRO_CONFIG_1, VAL_5);
}


uint16_t accelerometer_x_axis(void){
   uint16_t accel_x_axis = 0;
   accel_x_axis = read_register(IMU, 0x2E);
   printf("ax = %u\n", accel_x_axis);
   return accel_x_axis;
}
