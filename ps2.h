/*
 * ps2.h
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */

#ifndef PS2_H_
#define PS2_H_

#include <stdbool.h>

extern volatile uint32_t PS2_X_DIR;

extern volatile uint32_t PS2_Y_DIR;

extern volatile bool ALERT_PS2_UPDATE;

void ece353_ADC14_PS2_XY_COMP(void);

/***** * Initialize hardware resources used to control RGBLED *****/
void ece353_MKII_RGB_IO_Init(bool);

void ece353_RGB_LED_Init();



/******* * Turn RGBLED ON/Off. *
 * Parameters *  red_on      :   if true,  turn RGBLED.RED on * if false, turn RGBLED.RED off *  green_on    :   if true,  turn RGBLED.GREEN on *   if false, turn RGBLED.GREEN off *  blue_on     :   if true,  turn RGBLED.BLUE on *                  if false, turn RGBLED.BLUE off *****************************************************/
void ece353_RGB_LED(bool red_on, bool green_on, bool blue_on);

void ADC14_IRQHandler(void);

#endif /* PS2_H_ */
