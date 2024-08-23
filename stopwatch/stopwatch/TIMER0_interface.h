/*
 * TIMER0_interface.h
 *
 * Created: 26/09/2023 15:39:26
 *  Author: AMIT
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_



#define  TIMER_STOPE        0x00 
#define  NO_PRESCALER       0x01
#define  _8_PRESCALER       0x02
#define  _64_PRESCALER      0x03
#define  _256_PRESCALER     0x04
#define  _1024_PRESCALER    0x05


#define TIMER0_PRESCALER      _64_PRESCALER



void TIM0_Vid_Init(void)  ;
void TIM0_Vid_DelayMs(u32 copy_u32_delay) ; 
void TIM0_Vid_DelayUs(u32 copy_u32_delay) ; 

#endif /* TIMER0_INTERFACE_H_ */