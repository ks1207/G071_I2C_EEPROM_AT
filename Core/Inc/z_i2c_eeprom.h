/*
 * z_i2c_eeprom.h
 *
 *  Created on: Nov 30, 2023
 *      Author: ks1207
 */

#ifndef INC_Z_I2C_EEPROM_H_
#define INC_Z_I2C_EEPROM_H_

//&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT

//project depending parameter
#define EE_PORT hi2c1			// here are using I2C port
#define PARAM_EEADDR	0		//memory position

//I2C device depending parametr

//24C32
//#define EE_I2C_ADDR 0xA0		//I2C device Address
//#define EE_PAGE_LEN  32			// size of EEPROM memory page

//24C256
#define EE_I2C_ADDR 0xA0		//I2C device Address
#define EE_PAGE_LEN  64			// size of EEPROM memorz page (64 bytes for AT...)

//24C512
//#define EE_I2C_ADDR 0xA0		//I2C device Address
//#define EE_PAGE_LEN  128		// size of EEPROM memory page

// HAL api parameter
#define ETH_AVAIL_TRIALS 500		// no. of attempts testing EEPROM availability-never below 500
#define ETH_AVAIL_TIMEOUT 1	// timeout for each availability trial-put any value: no impact
#define I2C_COMM_TIMEOUT  10	// timeout for I2C communication

void test_EEPROM ();
uint8_t write_s_EEPROM(uint16_t addr, char* data);
uint8_t write_ns_EEPROM(uint16_t addr, char* data,uint8_t size);
uint8_t read_p_EEPROM(uint16_t addr, char* data);

#endif /* INC_Z_I2C_EEPROM_H_ */
