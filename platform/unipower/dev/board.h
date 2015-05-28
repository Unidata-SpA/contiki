/** 
 * \addtogroup cc2538dk
 * @{
 *
 * \defgroup cc2538-smartrf Unipower Peripherals
 *
 * Defines related to the Unipower
 *
 * This file provides connectivity information on LEDs, Buttons, UART and
 * other SmartRF peripherals
 *
 * Notably, PC0 is used to drive LED1 as well as the USB D+ pullup. Therefore
 * when USB is enabled, LED1 can not be driven by firmware.
 *
 * This file can be used as the basis to configure other platforms using the
 * cc2538 SoC.
 * @{
 *
 * \file
 * Header file with definitions related to the I/O connections on the
 * Unipower
 *
 * \note   Do not include this file directly. It gets included by contiki-conf
 *         after all relevant directives have been set.
 */
#ifndef BOARD_H_
#define BOARD_H_

#include "dev/gpio.h"
#include "dev/nvic.h"
/*---------------------------------------------------------------------------*/
/** \name SmartRF LED configuration
 *
 * LED on the Unipower are connected as follows:
 * - LED (Red)    -> PD1
 * @{
 */
/*---------------------------------------------------------------------------*/
/* Some files include leds.h before us, so we need to get rid of defaults in
 * leds.h before we provide correct definitions */
#undef LEDS_GREEN
#undef LEDS_YELLOW
#undef LEDS_RED
#undef LEDS_CONF_ALL

#define LEDS_RED    2 /**< LED  -> PD1 */
#define LEDS_YELLOW    LEDS_RED /**In this board there's only one led */
#define LEDS_GREEN     LEDS_RED /**In this board there's only one led */
#define LEDS_ORANGE    LEDS_RED /**In this board there's only one led */

/* Notify various examples that we have LEDs */
#define PLATFORM_HAS_LEDS        1
/** @} */
/*---------------------------------------------------------------------------*/
/** \name USB configuration
 *
 * The USB pullup is driven by PC0
 */
#define USB_PULLUP_PORT          GPIO_C_NUM
#define USB_PULLUP_PIN           0
/** @} */
/*---------------------------------------------------------------------------*/
/** \name UART configuration
 *
 * On the Unipower, the UART (XDS back channel) is connected to the
 * following ports/pins
 * - RX:  PA0
 * - TX:  PA1
 * - CTS: PB0 (Can only be used with UART1)
 * - RTS: PD3 (Can only be used with UART1)
 *
 * We configure the port to use UART0. To use UART1, replace UART0_* with
 * UART1_* below.
 * @{
 */
#define UART0_RX_PORT            GPIO_A_NUM
#define UART0_RX_PIN             0

#define UART0_TX_PORT            GPIO_A_NUM
#define UART0_TX_PIN             1

#define UART1_CTS_PORT           GPIO_B_NUM
#define UART1_CTS_PIN            0

#define UART1_RTS_PORT           GPIO_D_NUM
#define UART1_RTS_PIN            3
/** @} */
/*---------------------------------------------------------------------------*/
/** \name i2c configuration
 *
 * On the Unipower, the i2c is connected to the
 * following ports/pins
 * - SDA:  PC6
 * - SCL:  PC5
 *
 * @{
 */
#define I2C_SDA_PORT    GPIO_C_NUM
#define I2C_SDA_PIN     6                
#define I2C_SCL_PORT    GPIO_C_NUM
#define I2C_SCL_PIN     5
/** @} */
/*---------------------------------------------------------------------------*/
/** \name Serial Backdoor enable and definition
 *
 * On the Unipower, the backdoor pin to flash new fw
 * is connected on PA6 pin, Active low. To flash new fw
 * hold the reset button and the backdoor one, then 
 * release the reset, and after a liltte while
 * the backdoor
 *
 * @{
 */
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR	1 /**<Enable the boot loader backdoor */
#undef FLASH_CCA_CONF_BOOTLDR_BACKDOOR_PORT_A_PIN
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR_PORT_A_PIN 6 /**< Pin PA_6  activates the boot loader */
#undef FLASH_CCA_CONF_BOOTLDR_BACKDOOR_ACTIVE_HIGH
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR_ACTIVE_HIGH 0 /**< A logic low level activates the boot loader */
/** @} */
/*---------------------------------------------------------------------------*/
/** \name Definition of output to control alimentation on J9 and J10 connector
 *
 * On the Unipower, we have 4 MOS to control the alimentation aìon pheriperics
 * connected on J9 and J10. These are the connection:
 * - MOS1(Vcc-3.3 on J9):  		PD0
 * - MOS2(Vloc-5-12 on J9):  	PC1
 * - MOS3(Vcc-3.3 on J10):  	PC2
 * - MOS4(Vloc-5-12 on J10): 	PC3
 *
 * @{
 */
#define VCC_J9_EN_BASE GPIO_D_BASE
#define VCC_J9_EN_PIN_MASK 0x01
#define VCC_J9_EN_NUM GPIO_D_NUM
#define VCC_J9_EN_PIN 0

#define VCC_J10_EN_BASE GPIO_C_BASE
#define VCC_J10_EN_PIN_MASK 0x04
#define VCC_J10_EN_NUM GPIO_C_NUM
#define VCC_J10_EN_PIN 2

#define VLOC_J9_EN_BASE GPIO_C_BASE
#define VLOC_J9_EN_PIN_MASK 0x02
#define VLOC_J9_EN_NUM GPIO_C_NUM
#define VLOC_J9_EN_PIN 1

#define VLOC_J10_EN_BASE GPIO_C_BASE
#define VLOC_J10_EN_PIN_MASK 0x08
#define VLOC_J10_EN_NUM GPIO_C_NUM
#define VLOC_J10_EN_PIN 3
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name ADC configuration
 *
 * These values configure which CC2538 pins and ADC channels to use for the ADC
 * inputs.
 *
 * ADC inputs can only be on port A.
 * @{
 */
 	//to add if there will be a adc primary input.
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name SPI configuration
 *
 * These values configure which CC2538 pins to use for the SPI lines.
 * @{
 */
#define SPI_CLK_PORT             GPIO_A_NUM /**< Clock port */
#define SPI_CLK_PIN              2          /**< Clock pin */
#define SPI_MOSI_PORT            GPIO_A_NUM /**< MOSI port */
#define SPI_MOSI_PIN             4          /**< MOSI pin */
#define SPI_MISO_PORT            GPIO_A_NUM /**< MISO port */
#define SPI_MISO_PIN             5          /**< MISO pin */
/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Device string used on startup
 * @{
 */
#define BOARD_STRING "Unipower board"
/** @} */

#endif /* BOARD_H_ */

/**
 * @}
 * @}
 */
