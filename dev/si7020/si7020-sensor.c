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
 * This file is part of the Contiki operating system.
 *
 */

 /**
 * \file
 *  Architecture-specific definitions for the si7020 sensor unipower board.
 * \author
 *  Matteo Di Fraia <difraia.matteo@gmail.com>
 */

#include <stdlib.h>

#include "contiki.h"
#include "lib/sensors.h"
#include "dev/si7020/si7020.h"
#include "dev/si7020/si7020-sensor.h"

const struct sensors_sensor si7020_sensor;

enum {
  ON, OFF
};
static uint8_t state = OFF;

/*---------------------------------------------------------------------------*/
static int
value(int type)
{
  switch(type) {
    /* Temperature reading. */
  case SI7020_SENSOR_TEMP:
    return si7020_temp();;
    /* Umidity reading. */
  case SI7020_SENSOR_HUMIDITY:
    return si7020_humidity();
}
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
status(int type)
{
  switch(type) {
  case SENSORS_ACTIVE:
  case SENSORS_READY:
    return (state == ON);
  }
  return 0;
}

/*---------------------------------------------------------------------------*/
/*
* When you call SENSOR_ACTIVATE(si7020_sensor) Contiki call (sensor).configure(SENSORS_ACTIVE, 1)
* so the configure function isn't useless.
* When you call SENSOR_ACTIVATE(si7020_sensor) Contiki call (sensor).configure(SENSORS_ACTIVE, 0)
*/
static int
configure(int type, int c)
{
  switch(type) {
  case SENSORS_ACTIVE:
    if(c) {
      //we want to activate the sensor
      if(!status(SENSORS_ACTIVE)) {
        si7020_init();
        state = ON;
      }
    } else {
      //si7020_off(); function not implemented
      state = OFF;
    }
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(si7020_sensor, "si7020",
	       value, configure, status);
