/*
 * stopwatch.c
 *
 * Created: 9/27/2023 5:52:10 PM
 * Author : saiko_stores
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "Interrupt_vector.h"
#include "LCD_interface.h"
#include "LCD_config.h"


int count =0;
int hr=0 , min=0,sec=0;
int main(void)
{
	
	   
	/*  set data port --> output  */
	DIO_Vid_Set_Port_Dir(LCD_DPORT,PORT_OUTPUT) ;
	/* set control pins --> output */
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RS_PIN,OUTPUT) ;
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RW_PIN,OUTPUT) ;
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_EN_PIN,OUTPUT) ;
	
	LCD_Vid_Init() ;
    TIM0_Vid_Init() ;
	// LCD_Vid_Send_String("manon"); 
 

    while (1) 
    {
		

    }
}
ISR(TIMER0_OVF){
	static u8 i=10;
	static u8 j=7;
	static u8 k=4;
	count++ ;
	
	if(count==10){
		 
		   LCD_Vid_GOTOXY(3,0);
		   LCD_Vid_Send_Number(0);
		   LCD_Vid_Send_Number(hr);
		   LCD_Vid_Send_String(":");
		   LCD_Vid_Send_Number(0);
		   LCD_Vid_GOTOXY(j,0);
		   LCD_Vid_Send_Number(min);
		   LCD_Vid_Send_String(":");
		   LCD_Vid_Send_Number(0);
		   LCD_Vid_GOTOXY(i,0);
		   LCD_Vid_Send_Number(sec);
	     sec++;
	if(sec>9){
		i=9;
		if(sec==61){
			
			sec=0;
			i=9;
			LCD_Vid_GOTOXY(i,0);
		    LCD_Vid_Send_Number(0);
			LCD_Vid_GOTOXY(i+1,0);
			LCD_Vid_Send_Number(0);
			min++;
			if(min>9){
				j=6;
				if(min==60){
					min=0;
					j=6;
					LCD_Vid_GOTOXY(j,0);
					LCD_Vid_Send_Number(0);
					LCD_Vid_GOTOXY(j+1,0);
					LCD_Vid_Send_Number(0);
					hr++;
					if(hr>9){
						k=3;
					}
					j=7;
				}
			}
			
			i=10;
		}	
	}
	
	
	

	}
	if(count==20){

	
	count=0 ;
}
}



