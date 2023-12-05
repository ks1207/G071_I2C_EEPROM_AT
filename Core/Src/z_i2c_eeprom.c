/*
 * z_i2c_eeprom.c
 *
 *  Created on: Nov 30, 2023
 *      Author: ks1207
 */

#include "main.h"
extern I2C_HandleTypeDef hi2c1;

void test_EEPROM ()
{
	uint16_t time;
	uint16_t delta[7];
	uint8_t result[7];
	uint8_t data[EE_PAGE_LEN];

	__NOP();
	TIM7->EGR=1;
	HAL_Delay(1);

	//test 0 -checking (a free) EEPROM availability
	time= TIM7->CNT;
	result[0]=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);
	delta[0]=TIM7->CNT-time;

	//test 1 -reading 1 byte from EEPROM
	time= TIM7->CNT;
	result[1]=HAL_I2C_Mem_Read(&EE_PORT, EE_I2C_ADDR, PARAM_EEADDR, I2C_MEMADD_SIZE_16BIT, data, 1, I2C_COMM_TIMEOUT);
	delta[1]=TIM7->CNT-time;

	//test 4 -waiting for device free after writing 1 byte
	time= TIM7->CNT;
	result[4]=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);
	delta[4]=TIM7->CNT-time;


	//test 2 -reading a full EEPROM (in this case 64 bytes)
	time= TIM7->CNT;
	result[2]=HAL_I2C_Mem_Read(&EE_PORT, EE_I2C_ADDR, PARAM_EEADDR, I2C_MEMADD_SIZE_16BIT, data, EE_PAGE_LEN, I2C_COMM_TIMEOUT);
	delta[2]=TIM7->CNT-time;

	//test 4 -waiting for device free after writing 1 byte
	time= TIM7->CNT;
	result[4]=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);
	delta[4]=TIM7->CNT-time;


	//test 3 -writing 1 byte from EEPROM
	time= TIM7->CNT;
	result[3]=HAL_I2C_Mem_Write(&EE_PORT, EE_I2C_ADDR, PARAM_EEADDR, I2C_MEMADD_SIZE_16BIT, data, 1, I2C_COMM_TIMEOUT);
	delta[3]=TIM7->CNT-time;

	//test 4 -waiting for device free after writing 1 byte
	time= TIM7->CNT;
	result[4]=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);
	delta[4]=TIM7->CNT-time;

	//test 5 -writing a64 byte EEPROM page
	time= TIM7->CNT;
	result[5]=HAL_I2C_Mem_Write(&EE_PORT, EE_I2C_ADDR, PARAM_EEADDR, I2C_MEMADD_SIZE_16BIT, data, EE_PAGE_LEN, I2C_COMM_TIMEOUT);
	delta[5]=TIM7->CNT-time;

	//test 6 -waiting for device free after writing 64 byte
	time= TIM7->CNT;
	result[6]=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);
	delta[6]=TIM7->CNT-time;

	__NOP();

}

/**************************
 * @brief				write string into EEPROM
 * @param 		addr  	EEPROM memori adress to start wrinting into
 * 		  		data	pointer to string to write into EEPROM
 * 		  				PLEASE NOTE: 	there is not check about
 * 		  				EEPROM page boundary override
 * @result		result code front I2C device
 * */

 uint8_t write_s_EEPROM(uint16_t addr, char* data)
 {
	 uint8_t result;
	 result=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);

	 if (result==HAL_OK)
	 {
		 result=HAL_I2C_Mem_Write(&EE_PORT, EE_I2C_ADDR, addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*) data, strlen(data)+1, I2C_COMM_TIMEOUT);
	 }
	 return result;
 }


 /**************************
  * @brief				write n characters from a string into EEPROM
  * @param 		addr  	EEPROM memori adress to start wrinting into
  * 	   		data	pointer to string to write into EEPROM
  * 	   		size	number of char to write into EEPROM
  * 		  			PLEASE NOTE: 	there is not check about
  * 		  				EEPROM page boundary override
  * @result				result code front I2C device
  * */

  uint8_t write_ns_EEPROM(uint16_t addr, char* data,uint8_t size)
  {
 	 uint8_t result;
 	 result=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);

 	 if (result==HAL_OK)
 	 {
 		 result=HAL_I2C_Mem_Write(&EE_PORT, EE_I2C_ADDR, addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*) data, size, I2C_COMM_TIMEOUT);
 	 }
 	 return result;
  }

  /**************************
   * @brief				read a full EEPROM page into a string
   * @param		addr	memory address to start reading
   * 			data	string pointer receiving data read
   * 					PLEASE NOTE: string size must be-> EEPAGE_LEN
   * @result			result code front I2C device
   *
   * *******************/
  uint8_t read_p_EEPROM(uint16_t addr, char* data)
  {
 	 uint8_t result;
 	 result=HAL_I2C_IsDeviceReady(&EE_PORT, EE_I2C_ADDR, ETH_AVAIL_TRIALS, ETH_AVAIL_TIMEOUT);

 	 if (result==HAL_OK)
 	 {
 		result=HAL_I2C_Mem_Read(&EE_PORT, EE_I2C_ADDR, addr, I2C_MEMADD_SIZE_16BIT, (uint8_t*) data, EE_PAGE_LEN, I2C_COMM_TIMEOUT);
 	 }
 	 return result;
  }
