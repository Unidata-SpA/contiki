/*
 * Copyright (c) 2015, Unidata and Sapienza University of Rome.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/*
 * Device driver for Silicon Labs SI7020, humidity and temperature sensor.
 */
 /**
 * \file
 *  Architecture-specific definitions for the si7020 sensor unipower board.
 * \author
 *  Matteo Di Fraia <difraia.matteo@gmail.com>
 */

#include "contiki.h"
#include <stdio.h>
#include "i2c.h"
#include "dev/si7020/si7020.h"
#include "si7020-arch.h"

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

        /*  Device address    */
#define SI7020_ADDR     0x40
        /*  Device bus speed  */
#define SI7020_BUS_SPEED I2C_SCL_FAST_BUS_SPEED
        /*  I2C PIN and port  */
#define SI7020_SDA_PIN  SI7020_ARCH_SDA_PIN
#define SI7020_SDA_PORT SI7020_ARCH_SDA_PORT
#define SI7020_SCL_PIN  SI7020_ARCH_SCL_PIN
#define SI7020_SCL_PORT SI7020_ARCH_SCL_PORT
        /*  Command code      */
#define SI7020_MEAS_RH_HM                  0xE5
#define SI7020_MEAS_RH_NHM                 0XF5
#define SI7020_MEAS_TEMP_HM                0XE3
#define SI7020_MEAS_TEMP_NHM               0XF3
#define SI7020_READ_TEMP_FROM_PREV_RH_MEAS 0XE0
#define SI7020_RESET                       0XFE
 
/*---------------------------------------------------------------------------*/
/*
 * Power up the device. The device can be used after an additional
 * 80ms waiting time. Default resolution is 14bit for temp and 12 bit for RH
 */
void
si7020_init(void)
{
  clock_delay_usec(80);
}

/*---------------------------------------------------------------------------*/
/*
 * Read temperature from previous RH measurements
 */
int
si7020_temp(void)
{

  int temp;
  int ms = 0;
  int ls = 0;
  /*  read the reg and return I2C_MASTER_ERR_NONE if everything ok  */
  i2c_init(SI7020_SDA_PORT, SI7020_SDA_PIN, SI7020_SCL_PORT, SI7020_SCL_PIN, SI7020_BUS_SPEED);
  /*  Sened command to read previous temp measurements from RH  */
  i2c_single_send(SI7020_ADDR, SI7020_READ_TEMP_FROM_PREV_RH_MEAS);
  /*  Prepare to receive data  */            
  i2c_master_set_slave_address(SI7020_ADDR, I2C_RECEIVE);
  /*   we are going to receive the  MS byte of reading  */
  i2c_master_command(I2C_MASTER_CMD_BURST_RECEIVE_START);
  while(i2c_master_busy());
  temp = i2c_master_error();
  if(temp == I2C_MASTER_ERR_NONE) {
    ms = i2c_master_data_get();
  }
  /*   we are going to receive the  LS byte of reading and it's the last  */
  i2c_master_command(I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
  while(i2c_master_busy());
  temp = i2c_master_error();
  if(temp == I2C_MASTER_ERR_NONE) {
    ls = i2c_master_data_get();
  }
  temp = 0;
  temp = ((ms << 8) | (ls & 0xFF));
  /*  convert data to °C as datasheet says  */
  temp = ((176 * temp)/65536) - 47;
  return temp;
}
/*---------------------------------------------------------------------------*/
/*
 * Call may take up to 15ms.
 */
unsigned int
si7020_humidity(void)
{
  int temp;
  int ms = 0;
  int ls = 0;
  i2c_init(SI7020_SDA_PORT, SI7020_SDA_PIN, SI7020_SCL_PORT, SI7020_SCL_PIN, SI7020_BUS_SPEED);
  /*  send command to perform a reading of Relative humidity, hold master bus  */
  i2c_single_send(SI7020_ADDR, SI7020_MEAS_RH_HM);      
  while(i2c_master_busy());
  i2c_master_set_slave_address(SI7020_ADDR, I2C_RECEIVE);
  /*   we are going to receive the  MS byte of reading  */
  i2c_master_command(I2C_MASTER_CMD_BURST_RECEIVE_START);
  while(i2c_master_busy());
  temp = i2c_master_error();
  if(temp == I2C_MASTER_ERR_NONE) {
    ms = i2c_master_data_get();
  }
  /*   we are going to receive the  LS byte of reading and it's the last  */
  i2c_master_command(I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
  while(i2c_master_busy());
  temp = i2c_master_error();
  if(temp == I2C_MASTER_ERR_NONE) {
    ls = i2c_master_data_get();
  }
  temp = 0;
  temp = ((ms << 8) | (ls & 0xFF));
  /*  convert data to %RH as datasheet says  */
  temp = ((125 * temp)/ 65536) - 6;
  /*   Round result for error, as datasheet says */
  if (temp < 0) temp = 0;
  if (temp > 100) temp = 100;
  return temp;

}
/*---------------------------------------------------------------------------*/
/*
 * Reset device. Return I2C_MASTER_ERR_NONE if everything ok.
 */
int
si7020_reset(void)
{
  return i2c_single_send(SI7020_ADDR, SI7020_RESET);
}
/*---------------------------------------------------------------------------*/
