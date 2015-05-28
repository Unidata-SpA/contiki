#ifndef POWER_CONNCTOR_H
#define POWER_CONNCTOR_H

#define VLOC_J9		0x02
#define VCC_J10		0x04
#define VLOC_J10	0x08
#define VCC_J9		0x01


void init_power_connector();

void enable_all_power();

void disable_all_power();

void enable_specific_power(int mos);

void disable_specific_power(int mos);

#endif /* POWER_CONNCTOR_H */