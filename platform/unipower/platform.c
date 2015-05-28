#include "contiki.h"
#include "platform.h"
#include "dev/leds.h"
#include "dev/power-connector.h"

void
platform_init_post_initial()
{
}

void
platform_init_post_networking()
{
	init_power_connector();
}

void
platform_init_end()
{
	/*	the led blink when low value is put on the gpio. So to power off the led we need to set the gpio	*/
	leds_on(LEDS_RED);
	
}

