/*
 * File:   lcd.c
 * Author: DELL
 *
 * Created on April 14, 2022, 2:14 AM
 */

#include "lcd.h"


void LCD_DATA(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0x00;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
}