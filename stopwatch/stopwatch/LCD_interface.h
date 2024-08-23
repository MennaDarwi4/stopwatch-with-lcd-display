/*
 * LCD_interface.h
 *
 * Created: 29/08/2023 16:38:44
 *  Author: AMIT
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define  FOUR_BIT_MODE    0
#define  EIGHT_BIT_MODE   1


#define  LCD_MODE     FOUR_BIT_MODE  

/*   Commands  */
#define  LCD_CLR      0x01 
#define  LCD_RETURN_HOME  0x02

/*  LINES */

#define  ROW1       0 
#define  ROW2       1 

#define COL1        0
#define COL2        1
#define COL3        2
#define COL4        3
#define COL5        4
#define COL6        5
#define COL7        6
#define COL8        7
#define COL9        8
#define COL10       9
#define COL11       10
#define COL12       11
#define COL13       12
#define COL14       13
#define COL15       14
#define COL16       15
/*****************************************************************************
* Function Name: LCD_Vid_Send_Command
* Purpose      : Send command to lcd 
* Parameters   : copy_u8_command
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_Command(u8 copy_u8_command) ;
/*****************************************************************************
* Function Name: LCD_Vid_Send_Data
* Purpose      : Send data to lcd 
* Parameters   : copy_u8_data 
* Return value : void
*****************************************************************************/
void LCD_Vid_Send_Data(u8 copy_u8_data) ;

/*****************************************************************************
* Function Name: LCD_Vid_Init
* Purpose      : initialized LCD 
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_Vid_Init(void) ; 

void LCD_Vid_Send_String(u8 * add_u8_str) ; 

void LCD_Vid_GOTOXY(u8 copy_u8_x , u8 copy_u8_y) ;

void LCD_Vid_Send_Special_Char(u8 copy_u8_x  ,u8 copy_u8_y , u8 copy_u8_pattern , u8 copy_u8_data[8]) ;

void LCD_Vid_Send_Number(u32 copy_u32_number);
#endif /* LCD_INTERFACE_H_ */