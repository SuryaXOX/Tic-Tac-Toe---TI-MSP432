/*
 * timer32.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */

#include "timer32.h"
#include "tic_tac_toe.h"

//set a global variable that indicates that the button has been pressed.
extern volatile bool S2_PRESSED = false;

//set a global variable that indicates that the button has been pressed.
extern volatile bool PRESSED = false;

//set a global variable that indicates that the LCD can be updated.
extern volatile bool UPDATE_LCD = false;

// Add a global variable that holds the most recent value of the X direction
extern volatile uint32_t PS2_X_DIR = 0;

// Add a global variable that holds the most recent value of the X direction
extern volatile uint32_t PS2_Y_DIR = 0;

// Global variable that informs the application that the Window Camparator
// had detected a change
extern volatile bool ALERT_PS2_UPDATE = false;

//alert main application that the Window Comparator had detected a change
//extern volatile bool ALERT_PS2_UPDATE = false;

//Returns if MKII.S2 is currently pressed
bool ece353_MKII_S2(void)
     {
        if((P3->IN & BIT5) == 0)
                 {
                     return true;
                 }
                 else
                 {
                     return false;

                 }
     }

//Configure Timer32_1 to generate a periodic interrupt every 10ms
void ece353_T32_1_Interrupt_Ms()
      {
          //ticks = desired period / core clock period
          //20e-3/(1/3e6) = (3e6 * 20)/1000
          uint32_t ticks = ((SystemCoreClock * 10)/1000) - 1;

          //Stop the timer
          TIMER32_1->CONTROL = 0;

          // Set the load register
          TIMER32_1->LOAD = ticks;

          //Enable the Timer32 interrupt in NVIC
          __enable_irq();
          NVIC_EnableIRQ(T32_INT1_IRQn);
          NVIC_SetPriority(T32_INT1_IRQn,0);

          //Start Timer32 and enable interrupt
          TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE |     // turn timer on
                               TIMER32_CONTROL_MODE |       // periodic mode
                               TIMER32_CONTROL_SIZE |       // 32 bit timer
                               TIMER32_CONTROL_IE;          // enable interrupts


      }

//Configure Timer32_2 to generate a periodic interrupt every 100ms
void ece353_T32_2_Interrupt_Ms()
      {
          //ticks = desired period / core clock period
          //20e-3/(1/3e6) = (3e6 * 20)/1000
          uint32_t tick = ((SystemCoreClock * 100)/1000) - 1;

          //Stop the timer
          TIMER32_2->CONTROL = 0;

          // Set the load register
          TIMER32_2->LOAD = tick;

          //Enable the Timer32 interrupt in NVIC
          __enable_irq();
          NVIC_EnableIRQ(T32_INT2_IRQn);
          NVIC_SetPriority(T32_INT2_IRQn,0);

          //Start Timer32 and enable interrupt
          TIMER32_2->CONTROL = TIMER32_CONTROL_ENABLE |     // turn timer on
                               TIMER32_CONTROL_MODE |       // periodic mode
                               TIMER32_CONTROL_SIZE |       // 32 bit timer
                               TIMER32_CONTROL_IE;          // enable interrupts


      }

//Busy waits for 10mS and then returns.
void ece353_T32_1_wait_10ms()
  {

    // Stop the Timer
    TIMER32_1->CONTROL = 0;

    //Set the timer to a 16 bit timer, oneshot
    TIMER32_1->CONTROL |=  TIMER32_CONTROL_ONESHOT ;
    TIMER32_1->CONTROL |= BIT2;

    //Set the load register
    TIMER32_1->CONTROL |= TIMER32_CONTROL_PRESCALE_2;
    TIMER32_1->LOAD = 15000;

    //Start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;

    //Wait till it reaches 0
    while(TIMER32_1->VALUE != 0)
    {
        //timer is still counting, so wait
    }
  }

/*****************************************************
 * * Debounces S2 using Timer32_1.
 * * This function does not return until Button 2 has * been pressed for a minimum of 70 milliseconds.
 *  * * Parameters *      None * Returns *      None
 ***************************************************/
 void ece353_button2_wait_for_press()
 {
     int i;
     for(i=1 ; i<=7; i++)
     {
         ece353_T32_1_wait_10ms();
     if(ece353_MKII_S2() == false)
     {
         i = 1;
     }
     }
     return;
 }

//Timer32_1 ISR
//Detect when S2 has been pressed for a minimum of 70mS. This will require you to de-bounce S2.
//When S2 has been pressed, set a global variable that indicates that the button has been pressed.
//The user must release S2 before it can detect another button press.
//Every 10ms start an ADC14 conversion
void T32_INT1_IRQHandler(void)
{
    //ece353_button2_wait_for_press();
    static uint8_t button_state = 0x00;

    bool PRESSED = ece353_MKII_S2();
        // debounce push

    button_state = button_state << 1;

    if(PRESSED)
    {
       button_state |= 0x01;
    }

    if(button_state == 0x7F)
    {
        S2_PRESSED = true;
    }

    // Start the ADC conversion
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    // Clear the timer interrupt
    TIMER32_1->INTCLR = BIT0;

}

//Timer32_2 ISR
//Set a global variable that will be used to indicate that the LCD screen can be updated.
void T32_INT2_IRQHandler(void)
{

    UPDATE_LCD = true;

    // Clear the timer interrupt
    TIMER32_2->INTCLR = BIT0;

}

void ADC14_IRQHandler(void)
{
    // set the global variable that informs the application that the Window Comparator
    // had detected a change

    ALERT_PS2_UPDATE = true;


    // Determine if the HIIFG interrupt is active
    if (ADC14->IFGR1 & ADC14_IFGR1_HIIFG)
    {
        // Clear interrupt flag
        ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRHIIFG;

        // Turn off the HI interrupt
        ADC14->IER1 &= ~ADC14_IER1_HIIE;

        // Turn on LOW and IN interrupts
        ADC14->IER1 |= ADC14_IER1_LOIE;
        ADC14->IER1 |= ADC14_IER1_INIE;

    }

    // Determine if the LOIFG interrupt is active
    if (ADC14->IFGR1 & ADC14_IFGR1_LOIFG)
    {
        // Clear interrupt flag
        ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRLOIFG;

        // Turn off the LOW interrupt
        ADC14->IER1 &= ~ADC14_IER1_LOIE;

        // Turn on HI and IN interrupts
        ADC14->IER1 |= ADC14_IER1_HIIE;
        ADC14->IER1 |= ADC14_IER1_INIE;


    }

   //  Determine if the INIFG interrupt is active
    if (ADC14->IFGR1 & ADC14_IFGR1_INIFG)
    {
        // Clear interrupt flag
        ADC14->CLRIFGR1 |= ADC14_CLRIFGR1_CLRINIFG;

        // Turn off the IN interrupt
        ADC14->IER1 &= ~ADC14_IER1_INIE;

        // Turn on LOW and HI interrupts
        ADC14->IER1 |= ADC14_IER1_LOIE;
        ADC14->IER1 |= ADC14_IER1_HIIE;


    }

    // Read the X channel
    PS2_X_DIR = ADC14->MEM[0];

    // Read the Y channel
    PS2_Y_DIR = ADC14->MEM[1];

}
