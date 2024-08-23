/*
 * TIMER0_interface.c
 *
 * Created: 26/09/2023 15:40:24
 *  Author: AMIT
 */ 
#include "STD_TYPE.h" 
#include "BIT_MATH.h" 
#include "TIMER0_private.h" 
#include "TIMER0_interface.h"
#include "GIE_interface.h"


void TIM0_Vid_Init(void){
	
	/* select presclaer  */
	TCCR0_REG&=0b11111000 ; // start +  64 prescaler
	TCCR0_REG|=TIMER0_PRESCALER ; // start +  64 prescaler
	
	/* ENABLE INTERRUPT  */
	SET_BIT(TIMSK_REG,0) ; 
	/* ENABLE GLOBAL INTERRUPT  */
	GIE_Vid_Interrupt_Enable() ; 

	
}





void TIM0_Vid_DelayMs(u32 copy_u32_delay){
	
	      u32 count=0 ; 
		  
		  copy_u32_delay=(f32)copy_u32_delay/1.024 ; 
	
	
	while(count<copy_u32_delay){
		TCCR0_REG&=0b11111000 ; // start +  64 prescaler
		TCCR0_REG|=TIMER0_PRESCALER ; // start +  64 prescaler
		
		
		while(GET_BIT(TIFR_REG,0)==0) ;
		SET_BIT(TIFR_REG,0) ;
		
		count++ ;
	}
	TCCR0_REG=TIMER_STOPE ; // stop + noprescaler
	
}
//void TIM0_Vid_DelayUs(u32 copy_u32_delay){} 