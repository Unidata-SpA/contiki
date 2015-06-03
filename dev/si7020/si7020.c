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
 
				/* adr   command  r/w */

/* This can probably be reduced to 250ns according to data sheet. */
#ifndef delay_400ns
#define delay_400ns() _NOP()
#endif

/*---------------------------------------------------------------------------*/
/*
 * Power up the device. The device can be used after an additional
 * 11ms waiting time.
 */
void
si7020_init(void)
{
  
}

/*---------------------------------------------------------------------------*/
/*
 * read back value from register
 */
static unsigned int
rreg(uint8_t reg, uint8_t* data)
{
  //read the reg and return I2C_MASTER_ERR_NONE if everything ok
  i2c_init(SI7020_SDA_PORT, SI7020_SDA_PIN, SI7020_SCL_PORT, SI7020_SCL_PIN, SI7020_BUS_SPEED);
  i2c_single_send(SI7020_ADDR, reg);             //select the correct register
  return i2c_single_receive(SI7020_ADDR,  data);
}
/*---------------------------------------------------------------------------*/
/*
 * send command
 */
static unsigned int
scmd(uint8_t reg, uint8_t* data)
{
  
}
/*---------------------------------------------------------------------------*/
/*
 * Call may take up to 210ms.
 */
unsigned int
si7020_temp(void)
{
}
/*---------------------------------------------------------------------------*/
/*
 * Call may take up to 210ms.
 */
unsigned int
si7020_humidity(void)
{
}
/*---------------------------------------------------------------------------*/
#if 1 /* But ok! */
unsigned
si7020_sreg(void)
{
  
}
#endif
/*---------------------------------------------------------------------------*/

int
si7020_reset(void)
{
  
}
/*---------------------------------------------------------------------------*/
