#include "contiki.h"
#include "reg.h"
#include "dev/leds.h"
#include "dev/gpio.h"

#define LEDS_GPIO_PIN_MASK 0x02		/* PD1 is led red */

void
leds_arch_init(void)
{
	GPIO_SET_OUTPUT(GPIO_D_BASE, LEDS_GPIO_PIN_MASK);
}
/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
	return GPIO_READ_PIN(GPIO_D_BASE, LEDS_GPIO_PIN_MASK);
}
/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char leds)
{
  GPIO_WRITE_PIN(GPIO_D_BASE, LEDS_GPIO_PIN_MASK, leds);
}
/*---------------------------------------------------------------------------*/
