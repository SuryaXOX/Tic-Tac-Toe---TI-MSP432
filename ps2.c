/*
 * ps2.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */

#include "msp.h"
#include "ps2.h"
#include <stdbool.h>

// Add a global variable that holds the most recent value of the X direction
//extern volatile uint32_t PS2_X_DIR = 0;

// Add a global variable that holds the most recent value of the X direction
//extern volatile uint32_t PS2_Y_DIR = 0;

// Global variable that informs the application that the Window Camparator
// had detected a change
//extern volatile bool ALERT_PS2_UPDATE = false;

#define VOLT_0P60 745      // 0.60 /(3.3/4096)
#define VOLT_2P70 3351      // 2.70 /(3.3/4096)


/******************************************************************************
      * * Configure the IO pins for BOTH the X and Y directions of the analog * joystick.
      * The X direction should be configured to place the results in * MEM[0].  The Y direction should be configured to place the results in MEM[1].
      *  * * After BOTH analog signals have finished being converted, a SINGLE interrupt * should be generated.
      *   * * Parameters *      None
      *   * Returns *      None
      *   ******************************************************************************/

void ece353_ADC14_PS2_XY_COMP(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;

    // Configure the Y direction as an analog input pin.
    P6->SEL0 |= BIT4;
    P6->SEL1 |= BIT4;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // Indicate that this is a sequence of samples.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure CTL1 to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Set up the HI0 Window
    ADC14->HI0 = VOLT_2P70;

    // Set up the LO0 Window
    ADC14->LO0 = VOLT_0P60;

    // Associate the X direction analog signal with MEM[0], indicate the end of sequence,
    // turn on the window comparator
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15 | ADC14_MCTLN_WINC;

    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9 | ADC14_MCTLN_EOS | ADC14_MCTLN_WINC;



    // Enable interrupts when either the HI or LO thresholds of the window
    // comparator has been exceeded.  Disable all other interrupts
    ADC14->IER1 = ADC14_IER1_HIIE | ADC14_IER1_LOIE;

    ADC14->IER0 = ADC14_IER0_IE1; // Enabling the ADC interrupts

    // Enabling the ADC interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);


    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;

}


void ece353_RGB_LED_Init(void)
{
       //red led output initialization
        P2->DIR |= BIT0;

        //green led output initialization
        P2->DIR |= BIT1;

        //blue led output initialization
        P2->DIR |= BIT2;
}

void ece353_MKII_RGB_IO_Init(bool en_primary_function)
     {
         // Complete the comments below to identify which pins
         // control which LEDs.    //

         // Replace a and c with the correct port number
         // Replace b and d with the correct pin numbers.
         // RED      : P2.6
         // GREEN    : P2.4
         // BLUE     : P5.6

         // ADD CODE that configures the RED, GREEN, and
         // BLUE LEDs to be outputs

         P2->DIR |= BIT6;
         P2->DIR |= BIT4;
         P5->DIR |= BIT6;

         // ADD CODE that selects the Primary module function
         // for all 3 pins

         if(en_primary_function)
         {
             P2->SEL0 |= BIT6;
             P2->SEL1 &= ~BIT6;

             P2->SEL0 |= BIT4;
             P2->SEL1 &= ~BIT4;

             P5->SEL0 |= BIT6;
             P5->SEL1 &= ~BIT6;

         }
     }

void ece353_RGB_LED(bool red_on, bool green_on, bool blue_on)
{
    if(red_on)
      {
          //turn LED on
          P2->OUT |= BIT0;
      }
      else
      {
          //turn LED off
          P2->OUT &= ~BIT0;
      }
    if(green_on)
          {
              //turn LED on
              P2->OUT |= BIT1;
          }
          else
          {
              //turn LED off
              P2->OUT &= ~BIT1;
          }
    if(blue_on)
          {
              //turn LED on
              P2->OUT |= BIT2;
          }
          else
          {
              //turn LED off
              P2->OUT &= ~BIT2;
          }
}

