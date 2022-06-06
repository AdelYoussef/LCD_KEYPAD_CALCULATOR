/*
 * File:   main.c
 * Author: DELL
 *
 * Created on April 11, 2022, 12:14 AM
 */


#include <xc.h>
#include "config.h"
#include <pic16f877a.h>
#include "lcd.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define _XTAL_FREQ     4000000

void LCD_DATA(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
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

void LCD_CMD(unsigned char CMD)
{
  // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  LCD_DATA(CMD);
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
}
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0;
  // The Init. Procedure
  LCD_DATA(0x00);
  __delay_ms(30);
  __delay_us(LCD_EN_Delay);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(150);
  LCD_CMD(0x03);
  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}

void LCD_Write_Char(char Data)
{
  char Low4,High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}
void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
  {
    LCD_Write_Char(str[i]);
  }
  return;
}

void LCD_Clear()
{
  LCD_CMD(0);
  LCD_CMD(1);
}

void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}
void LCD_SR()
{
  LCD_CMD(0x01);
  LCD_CMD(0x0C);
}
void LCD_SL()
{
  LCD_CMD(0x01);
  LCD_CMD(0x08);
}
void clr(void)
{
    memset(val_one, 0, 10); // clearing the string
    memset(val_two, 0, 10); // clearing the string
    operation = ' ';
    c = 0;
}
void calc(float num_1 , float num_2 , char operation)
{
    float result = 0;
    char res [10] = {'\0'};
    switch (operation)
    {
        case '+':
            result = num_1 + num_2;
            break;
        case '-':
            result = num_1 - num_2;
            break;
        case '*':
            result = num_1 * num_2;
            break;
        case '/':
            result = num_1 / num_2;
            break;
            
       
    }
    clr();
    sprintf(res, "%f", result);
    strcpy(val_one , res);
    
    LCD_Set_Cursor(1,2);
    LCD_Write_String(res);

}
void show(void)
{
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    LCD_Write_String(val_one); 
    LCD_Write_Char(operation);
    LCD_Write_String(val_two);
}

void append(char key)
{
    
    
    
        if (key == '+')
        {       
            operation = key ;
            c++;
            //show();
        }
        else if (key == '-')
        {
            operation = key ;
            c++;
            //show();
        }
        else if (key == '*')
        {
            operation = key ;
            c++;
            //show();
        }
        else if (key == '/')
        {
            operation = key ;
            c++;
            //show();
        }
        else if (key == '=')
        {
            LCD_Write_Char('=');
            val_1 = atof(val_one);
            val_2 = atof(val_two);
            calc(val_1 , val_2 , operation);
            

        }
        else if (key == 'c')
        {
            
            LCD_Clear();
            LCD_Set_Cursor(1,1);
            LCD_Write_String("clear \0");
            __delay_ms(500);
            LCD_Clear();
            clr();
        }

        else 
    {
        if(c==0)
        {
        strncat(val_one , &key , 1);
        //show();

        }
        else if(c>0)
        {
        strncat(val_two , &key , 1);
        //show();
        }
        
         


        
    }
        
    
    show();




}



void main(void) {
  
TRISB = 0xf0;
PORTB = 0x00;


LCD_Init();
LCD_Clear();
LCD_Set_Cursor(1,1);
LCD_Write_String("adel says hello \0");
__delay_ms(1000);
LCD_Clear();
  while(1)
  {
    
  for (int i=0 ; i<4 ; i++)
        {
      
            
            for (int j=0 ; j<4 ; j++)
            {
               PORTB = out [i];
               __delay_ms(15);
               if(PORTB & in[j])
               {
                   append(key[i][j]);
               }
            }

        }
  }
}
