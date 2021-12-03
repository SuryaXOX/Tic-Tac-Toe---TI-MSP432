/*
 * tic_tac_toe.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Surya Santhan Thenarasu
 */

#include "tic_tac_toe.h"
#include "ps2.h"
#include "timer32.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>


#define VOLT_0P60 745      // 0.60 /(3.3/4096)
#define VOLT_2P70 3351      // 2.70 /(3.3/4096)

extern volatile bool RESET = false;
extern volatile bool STOP = false;
extern volatile bool END = false;
extern volatile int row = 65;
extern volatile int col = 65;
extern volatile int x =0;
extern volatile int y =0;
extern volatile int x1=0;
extern volatile int y1= 0;
extern volatile bool X =true;


//extern void lcd_init(void)
//{
//
//}

/*******************************************************************************
* Function Name: tic_tac_toe_hw_init
********************************************************************************
* Summary: Initializes all the hardware resources required for tic tac toe game
*          (IO Pins, ADC14, Timer32_1, Timer32_2).
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_hw_init(void)
{
    //Configure Timer32_1 to generate a periodic interrupt every 10ms
     ece353_T32_1_Interrupt_Ms();

    //Configure Timer32_1 to generate a periodic interrupt every 100ms
    ece353_T32_2_Interrupt_Ms();

     //initialize ADC14
     ece353_ADC14_PS2_XY_COMP();



}

/*******************************************************************************
* Function Name: tic_tac_toe_example_board
********************************************************************************
* Summary: Prints out an example of what the tic-tac-toe board looks like
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_example_board(void)
{
    // Horizontal Lines
    lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);
    lcd_draw_rectangle(SCREEN_CENTER_COL,LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);

    //Vertical Lines
    lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH,LCD_COLOR_BLUE2);
    lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH,LINE_LENGTH,LCD_COLOR_BLUE2);

    // Top Row
    lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_RED,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_GREEN,LCD_COLOR_BLACK);

    // Center Row
    lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_CYAN,LCD_COLOR_BLACK);

    // Lower Row
    lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_GRAY,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BROWN,LCD_COLOR_BLACK);
}

void clear(int b[])
{

    if(b[0] == 0)
          {
          lcd_draw_image(LEFT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }


          if(b[1] == 0)
          {
          lcd_draw_image(CENTER_COL,UPPER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }

          if(b[2] == 0)
          {
          lcd_draw_image(RIGHT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }

          // Center Row
          if(b[3] == 0)
          {
          lcd_draw_image(LEFT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }
          if(b[4] == 0)
          {
          lcd_draw_image(CENTER_COL,CENTER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }
          if(b[5] == 0)
          {
          lcd_draw_image(RIGHT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }


          // Lower Row
          if(b[6] == 0)
          {
          lcd_draw_image(LEFT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }
          if(b[7] == 0)
          {
          lcd_draw_image(CENTER_COL,LOWER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }
          if(b[8] == 0)
          {
          lcd_draw_image(RIGHT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          }
}

//Prints the active square
void print_active_square(int b[], int r, int c, bool x)
{

      // Top Row
      if(b[0] == 0)
      {
      lcd_draw_image(LEFT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }


      if(b[1] == 0)
      {
      lcd_draw_image(CENTER_COL,UPPER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }

      if(b[2] == 0)
      {
      lcd_draw_image(RIGHT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }

      // Center Row
      if(b[3] == 0)
      {
      lcd_draw_image(LEFT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }
      if(b[4] == 0)
      {
      lcd_draw_image(CENTER_COL,CENTER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }
      if(b[5] == 0)
      {
      lcd_draw_image(RIGHT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }


      // Lower Row
      if(b[6] == 0)
      {
      lcd_draw_image(LEFT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }
      if(b[7] == 0)
      {
      lcd_draw_image(CENTER_COL,LOWER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }
      if(b[8] == 0)
      {
      lcd_draw_image(RIGHT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      }

 int i;
 for(i =0;i<8;i++)
 {
     if( ((b[i] != 1) && (b[i] != 2)))
     {
      if(x)
      {
        if(r==0 && c==0)
        {
            if(b[0] == 2)
            {
            lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }

        }
        else if(r==0 && c==1)
        {
            if(b[1]==2)
            {
            lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==0 && c==2)
        {
            if(b[2]==2)
            {
            lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==1 && c==0)
        {
            if(b[3]==2)
            {
            lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==1 && c==1)
        {
            if(b[4]==2)
            {
            lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==1 && c==2)
        {
            if(b[5]==2)
            {
            lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==2 && c==0)
        {
            if(b[6]==2)
            {
            lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==2 && c==1)
        {
            if(b[7]==2)
            {
            lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
        else if(r==2 && c==2)
        {
            if(b[8]==2)
            {
            lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
            lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_RED);
            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            }
        }
      }
      else
      {
          if(r==0 && c==0)
          {
              if(b[0] == 1)
              {
              lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
               lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
               lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }

          }
          else if(r==0 && c==1)
          {
              if(b[1] == 1)
              {
              lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
                 lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                 lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==0 && c==2)
          {
              if(b[2] == 1)
              {

              lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
                  lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                  lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==1 && c==0)
          {
              if(b[3] == 1)
              {
              lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
                  lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                  lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==1 && c==1)
          {
              if(b[4] == 1)
              {
              lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
              lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
              lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==1 && c==2)
          {
              if(b[5]==1)
              {
              lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
              lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
              lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==2 && c==0)
          {
              if(b[6]==1)
              {
              lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
              lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
              lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==2 && c==1)
          {
              if(b[7]==1)
              {
              lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
                  lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                  lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
          else if(r==2 && c==2)
          {
              if(b[8]==1)
              {
              lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_RED);
              lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_RED);
              }
              else
              {
                  lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                  lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
              }
          }
      }
    }
 }
}





void print_active_square1(int b[], int r, int c, bool x)
{


        if(r==0 && c==0)
        {
            if(x)
            {
            lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
             lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
             lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }

        }
        else if(r==0 && c==1)
        {
            if(x)
            {
            lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==0 && c==2)
        {
            if(x)
            {
            lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==1 && c==0)
        {
            if(x)
            {
            lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }

        }
        else if(r==1 && c==1)
        {
            if(x)
            {
            lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==1 && c==2)
        {
            if(x)
            {
            lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==2 && c==0)
        {
            if(x)
            {
            lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==2 && c==1)
        {
            if(x)
            {
            lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
        }
        else if(r==2 && c==2)
        {
            if(x)
            {
            lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
            lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }
            else
            {
                lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);

            }


        }





}
// Function that checks the win or tie condition for 'X' or 'O'
bool win(int b[])
{
    if ((b[0] == 1) && (b[1] == 1) &&  (b[2] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[3] == 1) && (b[4] == 1) &&  (b[5] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[6] == 1) && (b[7] == 1) &&  (b[8] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[0] == 1) && (b[3] == 1) &&  (b[6] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[1] == 1) && (b[4] == 1) &&  (b[7] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[2] == 1) && (b[5] == 1) &&  (b[8] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[0] == 1) && (b[4] == 1) &&  (b[8] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[2] == 1) && (b[4] == 1) &&  (b[6] == 1))
            {
            lcd_X_wins();
            return true;

            }
        else if ((b[0] == 2) && (b[1] == 2) &&  (b[2] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[3] == 2) && (b[4] == 2) &&  (b[5] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[6] == 2) && (b[7] == 2) &&  (b[8] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[0] == 2) && (b[3] == 2) &&  (b[6] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[1] == 2) && (b[4] == 2) &&  (b[7] == 2))
            {
            lcd_O_wins();
            return true;
            }

        else if ((b[2] == 2) && (b[5] == 2) &&  (b[8] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[0] == 2) && (b[4] == 2) &&  (b[8] == 2))
            {
            lcd_O_wins();
            return true;

            }
        else if ((b[2] == 2) && (b[4] == 2) &&  (b[6] == 2))
            {
            lcd_O_wins();
            return true;


            }
        else if ( ((b[0] == 1) || (b[0] == 2)) && ((b[1] == 1) || (b[1] == 2))
                && ((b[2] == 1) || (b[2] == 2)) && ((b[3] == 1) || (b[3] == 2))
                && ((b[4] == 1) || (b[4] == 2)) &&  ((b[5] == 1) || (b[5] == 2))
                && ((b[6] == 1) || (b[6] == 2)) && ((b[7] == 1) || (b[7] == 2))
                && ((b[8] == 1) || (b[8] == 2)) )
        {
            lcd_tie();
            return true;


        }

return false;
 }

// converts pointer indexes to row and col values
int pointer_row(int i, int j)
{
    int r;
    if(i==0 && j==0)
            {

                r=25;
          //      j=0;
            }
            else if(i==0 && j==1)
            {

                r=25;
            //    j=1;
            }
            else if(i==0 && j==2)
            {

                r=25;
           //     j=2;
            }
            else if(i==1 && j==0)
            {

                r=65;
             //   j=0;
            }
            else if(i==1 && j==1)
            {

                r=65;
           //     j=1;
            }
            else if(i==1 && j==2)
            {

                r=65;
            //    j=2;
            }
            else if(i==2 && j==0)
            {

                r=105;
            //    j=0;
            }
            else if(i==2 && j==1)
            {

                r=105;
            //    j=1;
            }
            else if(i==2 && j==2)
            {

                r=105;
           //     j=2;
            }
    return r;
}

// converts pointer indexes to row and col values
int pointer_col(int i, int j)
{
    int c;
    if(i==0 && j==0)
            {

                c=25;
          //      j=0;
            }
            else if(i==0 && j==1)
            {

                c=65;
            //    j=1;
            }
            else if(i==0 && j==2)
            {

                c=105;
           //     j=2;
            }
            else if(i==1 && j==0)
            {

                c=25;
             //   j=0;
            }
            else if(i==1 && j==1)
            {

                c=65;
           //     j=1;
            }
            else if(i==1 && j==2)
            {

                c=105;
            //    j=2;
            }
            else if(i==2 && j==0)
            {

                c=25;
            //    j=0;
            }
            else if(i==2 && j==1)
            {

                c=65;
            //    j=1;
            }
            else if(i==2 && j==2)
            {

                c=105;
           //     j=2;
            }
    return c;
}


// Function that prints the recently updated board
void print1(int b[])
{
    int i;
    for(i=0; i<8; i++)
    {
        if(b[i]==1)
        {
        switch(i)
        {
        case 0:
        lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 1:
        lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 2:
        lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 3:
        lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 4:
        lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 5:
        lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 6:
        lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 7:
        lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        case 8:
        lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
        lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
            break;
        }
        }
        else if(b[i]==2)
        {
            switch(i)
                    {
                    case 0:
                    lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 1:
                    lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 2:
                    lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 3:
                    lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 4:
                    lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 5:
                    lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 6:
                    lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 7:
                    lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    case 8:
                    lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_GREEN);
                    lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_GREEN);
                        break;
                    }
        }

    }

}
//Function that returns row location of the pointer
int pointer_loc_i(int r, int c)
{
    int i;
    //int j=0;

        if(r==25 && c==25)
        {

            i=0;
      //      j=0;
        }
        else if(r==25 && c==65)
        {

            i=0;
        //    j=1;
        }
        else if(r==25 && c==105)
        {

            i=0;
       //     j=2;
        }
        else if(r==65 && c==25)
        {

            i=1;
         //   j=0;
        }
        else if(r==65 && c==65)
        {

            i=1;
       //     j=1;
        }
        else if(r==65 && c==105)
        {

            i=1;
        //    j=2;
        }
        else if(r==105 && c==25)
        {

            i=2;
        //    j=0;
        }
        else if(r==105 && c==65)
        {

            i=2;
        //    j=1;
        }
        else if(r==105 && c==105)
        {

            i=2;
       //     j=2;
        }

        return i;
}

//Function that returns col location of the pointer
int pointer_loc_j(int r, int c)
{
   // int i=0;
    int j;

        if(r==25 && c==25)
        {

        //    i=0;
            j=0;
        }
        else if(r==25 && c==65)
        {

        //    i=0;
            j=1;
        }
        else if(r==25 && c==105)
        {

        //    i=0;
            j=2;
        }
        else if(r==65 && c==25)
        {

        //    i=1;
            j=0;
        }
        else if(r==65 && c==65)
        {

        //    i=1;
            j=1;
        }
        else if(r==65 && c==105)
        {

        //    i=1;
            j=2;
        }
        else if(r==105 && c==25)
        {

        //    i=2;
            j=0;
        }
        else if(r==105 && c==65)
        {

       //     i=2;
            j=1;
        }
        else if(r==105 && c==105)
        {

        //    i=2;
            j=2;
        }

        return j;
}



//Function to assign squares to player
void assign(int b[], int r, int c, bool X)
{


  if(X)
  {
    if(r==25 && c==25 && !(b[0]==2))
    {
        b[0] = 1;

    }
    else if(r==25 && c==65 && !(b[1]==2))
    {
        b[1] = 1;

    }
    else if(r==25 && c==105 && !(b[2]==2))
    {
        b[2] = 1;

    }
    else if(r==65 && c==25 && !(b[3]==2))
    {
        b[3] = 1;

    }
    else if(r==65 && c==65 && !(b[4]==2))
    {
        b[4] = 1;

    }
    else if(r==65 && c==105 && !(b[5]==2))
    {
        b[5] = 1;

    }
    else if(r==105 && c==25 && !(b[6]==2))
    {
        b[6] = 1;

    }
    else if(r==105 && c==65 && !(b[7]==2))
    {
        b[7] = 1;

    }
    else if(r==105 && c==105 && !(b[8]==2))
    {
        b[8] = 1;

    }
  }
  else
  {
      if(r==25 && c==25 && !(b[0]==1))
          {
              b[0] = 2;

          }
          else if(r==25 && c==65 && !(b[1]==1))
          {
              b[1] = 2;

          }
          else if(r==25 && c==105 && !(b[2]==1))
          {
              b[2] = 2;

          }
          else if(r==65 && c==25 && !(b[3]==1))
          {
              b[3] = 2;

          }
          else if(r==65 && c==65 && !(b[4]==1))
          {
              b[4] = 2;

          }
          else if(r==65 && c==105 && !(b[5]==1))
          {
              b[5] = 2;

          }
          else if(r==105 && c==25 && !(b[6]==1))
          {
              b[6] = 2;

          }
          else if(r==105 && c==65 && !(b[7]==1))
          {
              b[7] = 2;

          }
          else if(r==105 && c==105 && !(b[8]==1))
          {
              b[8] = 2;

          }
  }

}

void reset(int b[], int row, int col)
{

    // Horizontal Lines
    lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);
    lcd_draw_rectangle(SCREEN_CENTER_COL,LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);

    //Vertical Lines
    lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH,LCD_COLOR_BLUE2);
    lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH,LINE_LENGTH,LCD_COLOR_BLUE2);

    b[0]=0;
    b[1]=0;
    b[2]=0;
    b[3]=0;
    b[4]=0;
    b[5]=0;
    b[6]=0;
    b[7]=0;
    b[8]=0;

  if(b[0] == 0)
  {
      lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK);
  lcd_draw_image(LEFT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }


  if(b[1] == 0)
  {
      lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK);
  lcd_draw_image(CENTER_COL,UPPER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }

  if(b[2] == 0)
  {
      lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK);
  lcd_draw_image(RIGHT_COL,UPPER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }

  // Center Row
  if(b[3] == 0)
  {
      lcd_draw_rectangle(LEFT_COL, CENTER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(LEFT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }
  if(b[4] == 0)
  {
      lcd_draw_rectangle(CENTER_COL, CENTER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(CENTER_COL,CENTER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }
  if(b[5] == 0)
  {
      lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(RIGHT_COL,CENTER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }


  // Lower Row
  if(b[6] == 0)
  {
      lcd_draw_rectangle(LEFT_COL, LOWER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(LEFT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }
  if(b[7] == 0)
  {
      lcd_draw_rectangle(CENTER_COL, LOWER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(CENTER_COL,LOWER_ROW,32,32,Bitmaps_X,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }
  if(b[8] == 0)
  {
      lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, 36, 36, LCD_COLOR_BLACK);
  lcd_draw_image(RIGHT_COL,LOWER_ROW,32,32,Bitmaps_O,LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  }

    row=65;
    col=65;

    x = pointer_loc_i(row,col);
    y= pointer_loc_j(row,col);
    print_active_square(b,x,y,X);
}

/*******************************************************************************
* Function Name: tic_tac_toe_play_game
********************************************************************************
* Summary: Enters the code that plays the tic_tac_toe game.  Once called, this
*          function should never return!
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_play_game(void)
{

    int b[9] = {0, 0, 0,
                        0, 0, 0,
                        0, 0, 0};



            x = pointer_loc_i(row,col);
            y= pointer_loc_j(row,col);
            print_active_square(b,x,y,X);




            // Horizontal Lines
            lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);
            lcd_draw_rectangle(SCREEN_CENTER_COL,LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE2);

            //Vertical Lines
            lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH,LCD_COLOR_BLUE2);
            lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH,LINE_LENGTH,LCD_COLOR_BLUE2);





    while(1)
    {

            x1 = pointer_loc_i(row,col);
            y1 = pointer_loc_j(row,col);

            if(ALERT_PS2_UPDATE)
                    {
                        //modify cursor
                        ALERT_PS2_UPDATE = false;

                        if((PS2_X_DIR > VOLT_2P70) && (!STOP))
                       {
                            STOP = true;
                            if(col == 105)
                                {
                                    col = 25;
                                }
                                else
                                {
                                    col+=40;
                                }
                             x = pointer_loc_i(row,col);
                             y = pointer_loc_j(row,col);



                       }
                       else if((PS2_X_DIR < VOLT_0P60) && (!STOP))
                       {
                           STOP = true;
                           if(col == 25)
                           {
                               col=105;
                           }
                           else
                           {
                               col-=40;
                           }

                            x = pointer_loc_i(row,col);
                            y= pointer_loc_j(row,col);


                       }
                       else if((PS2_Y_DIR > VOLT_2P70) && (!STOP))
                        {
                           STOP = true;
                           if(row == 25)
                            {
                               row=105;
                            }
                           else
                             {
                                row-=40;
                             }

                            x = pointer_loc_i(row,col);
                            y= pointer_loc_j(row,col);


                        }
                       else if((PS2_Y_DIR < VOLT_0P60) && (!STOP))
                        {
                           STOP = true;
                           if(row == 105)
                             {
                                row = 25;
                             }
                           else
                             {
                                row+=40;
                             }

                            x = pointer_loc_i(row,col);
                            y= pointer_loc_j(row,col);


                         }

                    }




            if(S2_PRESSED)
                    {
                S2_PRESSED = false;
                    //modify 2D matrix


                assign(b, row, col, X);

                if(X)
                {
                    X=false;
                }
                else
                {
                    X=true;
                }

                    }

            if(win(b))
                {

                if(S2_PRESSED)// checks if S2 is pressed
                {
                    S2_PRESSED = false;
                   // Reset_Handler();
                    reset(b, row, col);// Resets the board
                }
                }




            if(UPDATE_LCD)//translate to LCD
              {
                UPDATE_LCD = false;


                if(STOP)
                {

                    STOP = false;
                   print1(b);
                   print_active_square( b, x, y, X);

                }

               }

   }
}


