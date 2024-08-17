#include <stdint.h>
#include "EdgeTrigger.h"
#include "../inc/tm4c123gh6pm.h"

void (*PeriodicTaskEdge)(uint8_t);   // user function

void EdgeTrigger_Init(void(*task)(uint8_t)){       
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
	PeriodicTaskEdge = task;
  GPIO_PORTE_DIR_R &= ~0x0F;    // (c) make PE0-3 in (built-in button)
  GPIO_PORTE_DEN_R |= 0x0F;     //     enable digital I/O on PE0-3
  GPIO_PORTE_IS_R &= ~0x0F;     // (d) PE0-3 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x0F;    //     PE0-3 is not both edges
  GPIO_PORTE_IEV_R |= 0x0F;    //     PE0-3 rising edge event
  GPIO_PORTE_ICR_R = 0x0F;      // (e) clear flag4
  GPIO_PORTE_IM_R |= 0x0F;      // (f) arm interrupt on PE0-3
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF1F)|0x000000A0; // (g) priority 5
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
}

extern "C" void GPIOE_Handler(void);

void GPIOE_Handler(void){
  GPIO_PORTE_ICR_R = 0x0F;      // acknowledge flag4
	(*PeriodicTaskEdge)((uint8_t) GPIO_PORTE_DATA_R & 0xF); 
}
