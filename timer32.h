/*
 * timer32.h
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */

#ifndef TIMER32_H_
#define TIMER32_H_

#include "msp.h"
#include <stdbool.h>
#include <stdint.h>

extern volatile bool S2_PRESSED;

//set a global variable that indicates that the LCD can be updated.
extern volatile bool UPDATE_LCD;

//extern volatile bool ALERT_PS2_UPDATE;

//Returns if MKII.S2 is currently pressed
bool ece353_MKII_S2(void);

//Configure Timer32_2 to generate a periodic interrupt every 10ms
void ece353_T32_1_Interrupt_Ms();

//Configure Timer32_2 to generate a periodic interrupt every 100ms
void ece353_T32_2_Interrupt_Ms();

//Busy waits for 10mS and then returns.
void ece353_T32_1_wait_10ms();

/*****************************************************
 * * Debounces S2 using Timer32_1.
 * * This function does not return until Button 2 has * been pressed for a minimum of 70 milliseconds.
 *  * * Parameters *      None * Returns *      None
 ***************************************************/
void ece353_button2_wait_for_press();

//Timer32_1 ISR
void T32_INT1_IRQHandler(void);

//Timer32_2 ISR
void T32_INT2_IRQHandler(void);


#endif /* TIMER32_H_ */
