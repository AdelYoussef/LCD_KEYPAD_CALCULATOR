#include <xc.h>


#define LCD_EN_Delay 500
#define LCD_DATA_PORT_D TRISC
#define LCD_RS_D TRISC4
#define LCD_EN_D TRISC5
#define RS RC4
#define EN RC5
#define D4 RC0
#define D5 RC1
#define D6 RC2
#define D7 RC3
 
//==============================================
//-----[ Prototypes For All LCD Functions ]-----
 
void LCD_Init(); // Initialize The LCD For 4-Bit Interface
void LCD_Clear(); // Clear The LCD Display
void LCD_SL(); // Shift The Entire Display To The Left
void LCD_SR(); // Shift The Entire Display To The Right
 
void LCD_CMD(unsigned char); // Send Command To LCD
void LCD_DATA(unsigned char); // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char); // Set Cursor Position
void LCD_Write_Char(char); // Write Character To LCD At Current Position
void LCD_Write_String(char*); // Write A String To LCD

int level = 0;
char val_one[10] = {'\0'};
char val_two[10] = {'\0'};
char operation = ' ';
float val_1 = 0 ;
float val_2 = 0 ;
int c = 0;
unsigned char out [4] = {0x01 , 0x02 , 0x04 , 0x08 };
unsigned char in [4] = {0x10 , 0x20 , 0x40 , 0x80 };
unsigned char key [4][4]= {{'7' , '8' , '9' , '/'},{'4' , '5' , '6' , '*'},{'1' , '2' , '3' , '-'},{'c' , '0' , '=' , '+'}};