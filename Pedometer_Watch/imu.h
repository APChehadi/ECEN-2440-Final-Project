/*
 * imu.h
 *
 *  Created on: Dec 9, 2019
 *      Author: adamp
 */

#ifndef IMU_H_
#define IMU_H_

#define DRV2605L    0x69        // 7-bit address
#define MODE        0x01
#define CONTROL3    0x1D

void config_imu(void (*toggle_routine)());

#endif /* IMU_H_ */
