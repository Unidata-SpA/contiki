
#include <stdio.h>
#include "contiki-conf.h"
#include "dev/gpio.h"
#include "dev/ioc.h"
#include "dev/power-connector.h"

void init_power_connector(){
	//disable vcc(3.3) on J9
	GPIO_SOFTWARE_CONTROL(VCC_J9_EN_BASE, VCC_J9_EN_PIN_MASK);      // passa il controllo via software
  	// http://sourceforge.net/p/contiki/mailman/message/33387577/
  GPIO_SET_OUTPUT(VCC_J9_EN_BASE, VCC_J9_EN_PIN_MASK);
  	//output enabled
  ioc_set_over(VCC_J9_EN_NUM, VCC_J9_EN_PIN, IOC_OVERRIDE_OE);
  GPIO_SET_PIN(VCC_J9_EN_BASE, VCC_J9_EN_PIN_MASK);

  	//disable vcc(3.3) on J10
  GPIO_SOFTWARE_CONTROL(VCC_J10_EN_BASE, VCC_J10_EN_PIN_MASK);      // passa il controllo via software
  	// http://sourceforge.net/p/contiki/mailman/message/33387577/
  GPIO_SET_OUTPUT(VCC_J10_EN_BASE, VCC_J10_EN_PIN_MASK);
  	//output enabled
  ioc_set_over(VCC_J10_EN_NUM, VCC_J10_EN_PIN, IOC_OVERRIDE_OE);
  GPIO_SET_PIN(VCC_J10_EN_BASE, VCC_J10_EN_PIN_MASK);

  	//disable vloc(5v) on J10
  GPIO_SOFTWARE_CONTROL(VLOC_J10_EN_BASE, VLOC_J10_EN_PIN_MASK);      // passa il controllo via software
  	// http://sourceforge.net/p/contiki/mailman/message/33387577/
  GPIO_SET_OUTPUT(VLOC_J10_EN_BASE, VLOC_J10_EN_PIN_MASK);
  	//output enabled
  ioc_set_over(VLOC_J10_EN_NUM, VLOC_J10_EN_PIN, IOC_OVERRIDE_OE);
  GPIO_SET_PIN(VLOC_J10_EN_BASE, VLOC_J10_EN_PIN_MASK);

  	//disable vloc(5v) on J9
  GPIO_SOFTWARE_CONTROL(VLOC_J9_EN_BASE, VLOC_J9_EN_PIN_MASK);      // passa il controllo via software
  	// http://sourceforge.net/p/contiki/mailman/message/33387577/
  GPIO_SET_OUTPUT(VLOC_J9_EN_BASE, VLOC_J9_EN_PIN_MASK);
  	//output enabled
  ioc_set_over(VLOC_J9_EN_NUM, VLOC_J9_EN_PIN, IOC_OVERRIDE_OE);
  GPIO_SET_PIN(VLOC_J9_EN_BASE, VLOC_J9_EN_PIN_MASK);

}

void enable_all_power(){
	GPIO_CLR_PIN(VCC_J9_EN_BASE, VCC_J9_EN_PIN_MASK);

  GPIO_CLR_PIN(VCC_J10_EN_BASE, VCC_J10_EN_PIN_MASK);

  GPIO_CLR_PIN(VLOC_J10_EN_BASE, VLOC_J10_EN_PIN_MASK);

  GPIO_CLR_PIN(VLOC_J9_EN_BASE, VLOC_J9_EN_PIN_MASK);
}

void disable_all_power(){
	GPIO_SET_PIN(VCC_J9_EN_BASE, VCC_J9_EN_PIN_MASK);

  GPIO_SET_PIN(VCC_J10_EN_BASE, VCC_J10_EN_PIN_MASK);

  GPIO_SET_PIN(VLOC_J10_EN_BASE, VLOC_J10_EN_PIN_MASK);

  GPIO_SET_PIN(VLOC_J9_EN_BASE, VLOC_J9_EN_PIN_MASK);
}

/*
*	Enable a specific mosfet.
*	Params:	could be any of the defines relative to the output in the power-connector.h. 
*			It could be a bitwise OR of more define.
*/
void enable_specific_power(int mos){
	GPIO_CLR_PIN(GPIO_C_BASE, (mos & 0x0E));
	GPIO_CLR_PIN(VCC_J9_EN_BASE, (mos & 0x01));
}

/*
* Disable a specific mosfet.
* Params: could be any of the defines relative to the output in the power-connector.h. 
*     It could be a bitwise OR of more define.
*/
void disable_specific_power(int mos){
  GPIO_SET_PIN(GPIO_C_BASE, (mos & 0x0E));
  GPIO_SET_PIN(VCC_J9_EN_BASE, (mos & 0x01));

}