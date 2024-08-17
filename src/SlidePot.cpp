// SlidePot.cpp
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "SlidePot.h"
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x08;      // 1) activate clock for Port D
	while((SYSCTL_PRGPIO_R&0x08) == 0){};
	GPIO_PORTD_DIR_R &= ~0x04;      // 2) make PD2 input
	GPIO_PORTD_AFSEL_R |= 0x04;     // 3) enable alternate fun on PD2
	GPIO_PORTD_DEN_R &= ~0x04;      // 4) disable digital I/O on PD2
	GPIO_PORTD_AMSEL_R |= 0x04;     // 5) enable analog fun on PD2
	SYSCTL_RCGCADC_R |= 0x01;       // 6) activate ADC0
	int volatile delay;
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
	delay = SYSCTL_RCGCADC_R;
	ADC0_PC_R = 0x01;               // 7) configure for 125K 
	ADC0_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority
	ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
	ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+5;  // 11) Ain9 (PE4)
	ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
	ADC0_IM_R &= ~0x0008;           // 13) disable SS3 interrupts
	ADC0_SAC_R = 5;
	ADC0_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
/////////////////JOYSTICK/////////////////////      
	SYSCTL_RCGCADC_R |= 0x00000002; // 1) activate ADC1
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // 1) activate clock for Port E
  delay = SYSCTL_RCGCGPIO_R;      // 2) allow time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_DIR_R &= ~0x30;      // 3) make PE4 PE5 input
  GPIO_PORTE_AFSEL_R |= 0x30;     // 4) enable alternate function on PE4 PE5
  GPIO_PORTE_DEN_R &= ~0x30;      // 5) disable digital I/O on PE4 PE5
                                  // 5a) configure PE4 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R&0xFF00FFFF;
  GPIO_PORTE_AMSEL_R |= 0x30;     // 6) enable analog functionality on PE4 PE5
  ADC1_PC_R &= ~0xF;              // 8) clear max sample rate field
  ADC1_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC1_SSPRI_R = 0x3210;          // 9) Sequencer 3 is lowest priority
  ADC1_ACTSS_R &= ~0x0004;        // 10) disable sample sequencer 2
  ADC1_EMUX_R &= ~0x0F00;         // 11) seq2 is software trigger
  ADC1_SSMUX2_R = 0x0089;         // 12) set channels for SS2
  ADC1_SSCTL2_R = 0x0060;         // 13) no TS0 D0 IE0 END0 TS1 D1, yes IE1 END1
  ADC1_IM_R &= ~0x0004;           // 14) disable SS2 interrupts
  ADC1_ACTSS_R |= 0x0004;         // 15) enable sample sequencer 2
}
//------------ADCIn------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_SpeedIn(void){  
	uint32_t data;
  ADC0_PSSI_R = 0x0008;            
  while((ADC0_RIS_R&0x08)==0){};   
  data = ADC0_SSFIFO3_R&0xFFF; 
  ADC0_ISC_R = 0x0008;
  return data;
}

void ADC_JoyIn(uint32_t data[2]){ 
  ADC1_PSSI_R = 0x0004;            // 1) initiate SS2
  while((ADC1_RIS_R&0x04)==0){};   // 2) wait for conversion done
  data[1] = ADC1_SSFIFO2_R&0xFFF;  // 3A) read first result
  data[0] = ADC1_SSFIFO2_R&0xFFF;  // 3B) read third result
  ADC1_ISC_R = 0x0004;             // 4) acknowledge completion
}

// constructor, invoked on creation of class
// m and b are linear calibration coeffients 
SlidePot::SlidePot(uint32_t m, uint32_t b){
	slope = m;
	offset = b;
}

void SlidePot::Save(uint32_t n){
// 1) save ADC sample into private variable
	data = n;
// 2) calculate distance from ADC, save into private variable
	distance = Convert(n);
// 3) set semaphore flag = 1
	flag = 1;
}
uint32_t SlidePot::Convert(uint32_t n){
  // use calibration data to convert ADC sample to distance
  return slope * data / 1000 + offset;
}

void SlidePot::Sync(void){
// 1) wait for semaphore flag to be nonzero
	while(flag == 0);
// 2) set semaphore flag to 0
	flag = 0;
}

uint32_t SlidePot::ADCsample(void){ // return ADC sample value (0 to 4095)
  // return last calculated ADC sample
  return data;
}

uint32_t SlidePot::Distance(void){  // return distance value (0 to 2000), 0.001cm
  // return last calculated distance in 0.001cm
  return distance;
}
