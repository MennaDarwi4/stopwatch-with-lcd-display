/*
 * LCD_interface.c
 *
 * Created: 8/29/2023 4:39:56 PM
 *  Author: saiko_stores
 */ 
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#define  F_CPU 16000000
#include <util/delay.h>

static void SHDATA(u8 copy_u8_data)
{
	u8 loc_u8_in =0;
	u8 loc_u8_pin[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN};
	for(loc_u8_in=0 ; loc_u8_in<4 ; loc_u8_in++)
	{
		DIO_Vid_Set_Pin_Val(LCD_DPORT,loc_u8_pin[loc_u8_in],GET_BIT(copy_u8_data,loc_u8_in));
	}
}

static void Send_Enable(void)
{
	/*SEND EN PULSE*/
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_EN_PIN,HIGH);
	_delay_ms(2);
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_EN_PIN,LOW);
}
void LCD_Vid_Send_Command(u8 copy_u8_command){
	
	/*SET RS PIN IN LCD TO SEND COMMAND*/
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,LOW);
	/*SET RW PIN IN LCD TO WRITE COMMAND*/
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW);
	#if LCD_MODE ==FOUR_BIT_MODE
	/*send HSB command*/
	SHDATA(copy_u8_command>>4);
	Send_Enable();
	/*LSB*/
	SHDATA(copy_u8_command);
	Send_Enable();
	#elif LCD_MODE==EIGHT_BIT_MODE
	/*send command*/
	DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_command);
	/*send pulse*/
	Send_Enable();
	#endif
}
	
void LCD_Vid_Send_Data(u8 copy_u8_data){
	
	/*SET RS PIN IN LCD TO SEND DATA*/
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RS_PIN,HIGH);
	/*SET RW PIN IN LCD TO WRITE DATA*/
	DIO_Vid_Set_Pin_Val(LCD_CPORT,LCD_RW_PIN,LOW);
	/*send data*/
	#if LCD_MODE ==FOUR_BIT_MODE
	/*send HSB command*/
	SHDATA(copy_u8_data>>4);
	Send_Enable();
	/*LSB*/
	SHDATA(copy_u8_data);
	Send_Enable();
	#elif LCD_MODE==EIGHT_BIT_MODE
	/*send command*/
	DIO_Vid_Set_Port_Val(LCD_DPORT,copy_u8_data);
	/*send pulse*/
	Send_Enable();
	#endif
}

void LCD_Vid_Init(void){
	
	_delay_ms(40) ;
	#if LCD_MODE==FOUR_BIT_MODE
		SHDATA(0b0010);
		Send_Enable();
		SHDATA(0b0010);
		Send_Enable();
		SHDATA(0b1000);
		Send_Enable();
	#elif LCD_MODE==EIGHT_BIT_MODE
	/* SEND  function set  */
	LCD_Vid_Send_Command(0x3C) ;
	#endif
	/* send ON/OFF Command  */
	LCD_Vid_Send_Command(0x0C) ;
	/* send  CLR command  */
	LCD_Vid_Send_Command(1) ;
}
void LCD_Vid_Send_String(u8 * add_u8_string)
{
	u8 loc_u8_index=0;
	while(add_u8_string[loc_u8_index] !='\0')
	{
		LCD_Vid_Send_Data(add_u8_string[loc_u8_index]);
		loc_u8_index++;
	}
}
void LCD_Vid_GOTOXY(u8 copy_u8_x ,u8 copy_u8_y){
	
	u8 loc_u8_DDRAMaddress=0;
	if(copy_u8_y==0){
	
		loc_u8_DDRAMaddress=copy_u8_x;	
	}
	else if(copy_u8_y==1){
		loc_u8_DDRAMaddress=copy_u8_x+0x40;
	}
	/*set DDRAM*/
	SET_BIT(loc_u8_DDRAMaddress,7);
	LCD_Vid_Send_Command(loc_u8_DDRAMaddress);
	
}
void LCD_Send_Special_Char(u8 copy_u8_x , u8 copy_u8_y , u8 copy_u8_pattern , u8 copy_u8_data[8]){
	
	u8 loc_u8_in;
	u8 loc_u8_CGRAMadd=copy_u8_pattern*8;
	/*set CGRAM*/
	SET_BIT(loc_u8_CGRAMadd,6);
	CLR_BIT(loc_u8_CGRAMadd,7);
	
	LCD_Vid_Send_Command(loc_u8_CGRAMadd);
	/*write data in CGRAM*/
	for(loc_u8_in=0 ; loc_u8_in<8 ; loc_u8_in++){
		LCD_Vid_Send_Data(copy_u8_data[loc_u8_in]);
	}
	/*back to DDRAM to display data*/
	LCD_Vid_GOTOXY(copy_u8_x,copy_u8_y);
	LCD_Vid_Send_Data(copy_u8_pattern);
}
void LCD_Vid_Send_Number(u32 copy_u32_number){
	
	s8 i=0;
	u8 array[10];
	if(copy_u32_number==0)
	{
		LCD_Vid_Send_Data('0');
		return ;
	}
	for(i=0 ; copy_u32_number!=0 ; i++){
		array[i]=copy_u32_number %10 +48;
		copy_u32_number /=10;
	}
	i--;
	while (i>=0)
	{
		LCD_Vid_Send_Data(array[i]);
		i--;
	}
}