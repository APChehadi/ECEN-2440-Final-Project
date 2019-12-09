/*
 * i2c.h
 *
 *  Created on: Dec 8, 2019
 *      Author: Adam Chehadi
 */

#ifndef I2C_H_
#define I2C_H_

void config_i2c(void);

uint8_t read_register(uint8_t address, uint8_t reg);

void write_register(uint8_t address, uint8_t reg, uint8_t value);

#endif /* I2C_H_ */
