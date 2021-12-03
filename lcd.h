/*
 * lcd.h
 *
 *  Created on: Oct 6, 2020
 *      Author: Joe Krachey
 *
 *
 *  Description:
 *  This header file contains some macros and functions that have
 *  been provided to aide in completing your assignment.  YOU DO NOT need
 *  to write any of the functions in this header file!
 *
 *  There are examples of how to use most of the functions in tic_tac_toe.c
 */
#include "msp.h"

#ifndef LCD_H_
#define LCD_H_

// LCD Screen Dimensions
#define LCD_VERTICAL_MAX                   132
#define LCD_HORIZONTAL_MAX                 132

#define LCD_COLOR_WHITE         0xFFFF
#define LCD_COLOR_BLACK         0x0000
#define LCD_COLOR_RED           0xF800
#define LCD_COLOR_GREEN         0x07E0
#define LCD_COLOR_GREEN2        0xB723
#define LCD_COLOR_BLUE          0x001F
#define LCD_COLOR_BLUE2         0x051D
#define LCD_COLOR_YELLOW        0xFFE0
#define LCD_COLOR_ORANGE        0xFBE4
#define LCD_COLOR_CYAN          0x07FF
#define LCD_COLOR_MAGENTA       0xA254
#define LCD_COLOR_GRAY          0x7BEF
#define LCD_COLOR_BROWN         0xBBCA

/*******************************************************************************
* Function Name: lcd_init
********************************************************************************
* Summary: Initializes the LCD
* Returns:
*  Nothing
*******************************************************************************/
extern void lcd_init(void);

/*******************************************************************************
* Function Name: lcd_draw_rectangle
********************************************************************************
* Summary: draws a filled rectangle centered at the coordinates set by x, y
* Returns:
*  Nothing
*******************************************************************************/
void lcd_draw_rectangle(
  uint16_t x,
  uint16_t y,
  uint16_t width_pixels,
  uint16_t height_pixels,
  uint16_t fColor
);

/*******************************************************************************
* Function Name: lcd_draw_image
********************************************************************************
* Summary: Prints an image centered at the coordinates set by x_start, y_start
* Returns:
*  Nothing
*******************************************************************************/
void lcd_draw_image(
  uint16_t x_start,
  uint16_t y_start,
  uint16_t image_width_pixels,
  uint16_t image_height_pixels,
  const uint8_t *image,
  uint16_t fColor,
  uint16_t bColor
);

/*******************************************************************************
* Function Name: lcd_X_wins
********************************************************************************
* Summary: Prints an image indicating that player X wins
* Returns:
*  Nothing
*******************************************************************************/
void lcd_X_wins(void);

/*******************************************************************************
* Function Name: lcd_O_wins
********************************************************************************
* Summary: Prints an image indicating that player O wins
* Returns:
*  Nothing
*******************************************************************************/
void lcd_O_wins(void);

/*******************************************************************************
* Function Name: lcd_tie
********************************************************************************
* Summary: Prints an image indicating that the game ended in a tie
* Returns:
*  Nothing
*******************************************************************************/
void lcd_tie(void);

#endif /* LCD_H_ */
