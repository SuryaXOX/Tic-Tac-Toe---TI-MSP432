/*
 * tic_tac_toe.h
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */
#ifndef __TIC_TAC_TOE_H__
#define __TIC_TAC_TOE_H__

#include <stdbool.h>
#include "lcd.h"
#include "ps2.h"
#include "timer32.h"
#include "tic_tac_toe_images.h"

#define SCREEN_X            132
#define SCREEN_Y            132

#define SCREEN_CENTER_COL    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_ROW    ((SCREEN_Y/2)-1)

#define LINE_WIDTH          4
#define LINE_LENGTH         (SCREEN_X - 1)

#define SQUARE_SIZE         32

#define PADDING             2

#define LEFT_COL                      (SCREEN_CENTER_COL - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_COL                    (SCREEN_CENTER_COL)
#define RIGHT_COL                     (SCREEN_CENTER_COL + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_ROW                     (SCREEN_CENTER_ROW - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_ROW                    (SCREEN_CENTER_ROW)
#define LOWER_ROW                     (SCREEN_CENTER_ROW + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define LOWER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)

#define LEFT_HORIZONTAL_LINE_X      (SCREEN_CENTER_COL - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define RIGHT_HORIZONTAL_LINE_X     (SCREEN_CENTER_COL + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)

//Function to assign squares to player
//int assign(int a[][], int r, int c);

extern volatile bool RESET;
extern volatile bool STOP;
extern volatile bool END;
//extern volatile uint16_t row;
//extern volatile uint16_t col;

/*******************************************************************************
* Function Name: lcd_init
********************************************************************************
* Summary: Initializes the LCD
* Returns:
*  Nothing
*******************************************************************************/
//extern void lcd_init(void);

extern volatile int x;
extern volatile int y;
extern volatile int x1;
extern volatile int y1;
extern volatile bool X;

// Function that checks the win or tie condition for 'X' or 'O'
bool win(int b[]);

void clear(int b[]);

// converts pointer indexes to row and col values
int pointer_row(int i, int j);

// converts pointer indexes to row and col values
int pointer_col(int i, int j);

void print_active_square1(int b[], int r, int c, bool X);

//Prints the active square
void print_active_square(int b[], int r, int c, bool x);

//Function that returns row location of the pointer
int pointer_loc_i(int r, int c);

//Function that returns col location of the pointer
int pointer_loc_j(int r, int c);

void assign(int b[], int r, int c, bool x);

// Function that prints the recently updated board
void print1(int b[]);

// RESET
//void Reset_Handler(void);
void reset(int b[], int row, int col);

/*******************************************************************************
* Function Name: tic_tac_toe_hw_init
********************************************************************************
* Summary: Initializes all the hardware resources required for tic tac toe game
*          (IO Pins, ADC14, Timer32_1, Timer32_2).
* Returns:
*  Nothing
*******************************************************************************/ 
void tic_tac_toe_hw_init(void);

/*******************************************************************************
* Function Name: tic_tac_toe_example_board
********************************************************************************
* Summary: Prints out an example of what the tic-tac-toe board looks like
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_example_board(void);

/*******************************************************************************
* Function Name: tic_tac_toe_play_game
********************************************************************************
* Summary: Enters the code that plays the tic_tac_toe game.  Once called, this
*          function should never return!
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_play_game(void);
#endif
