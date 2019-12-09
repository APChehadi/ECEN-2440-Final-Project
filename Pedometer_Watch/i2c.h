/*
 * i2c.h
 *
 *  Created on: Dec 8, 2019
 *      Author: Adam Chehadi
 */

#ifndef I2C_H_
#define I2C_H_

void init_i2c(void);

void rx_data(uint8_t address, uint8_t register);

void tx_data(uint8_t address, uint8_t register, uint8_t value);

#endif /* I2C_H_ */
