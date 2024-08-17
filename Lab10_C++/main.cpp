// main.cpp
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10 in C++

// Last Modified: 1/17/2020 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2017

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2017

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PD2/AIN5
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include "Random.h"
#include "PLL.h"
#include "SlidePot.h"
#include "Images.h"
#include "UART.h"
#include "Timer0.h"
#include "Timer1.h"
#include "EdgeTrigger.h"
#include <string>
#define NumGhosts 6
typedef enum {dead, alive, idle} status_t;
extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);
using namespace std;

struct Character{
	uint32_t x;
  uint32_t y;
	int8_t dx;
  int8_t dy;
  uint32_t prevx;
  uint32_t prevy;
	uint8_t w;
	uint8_t h;
	const uint16_t *image;
	const uint16_t *erase;
  status_t life;
};

Character GhostArray[NumGhosts];
Character player = {50, 50, 0, 0, 0, 0, 9, 9, pacman_open, pacman_open, alive};

Character CreateGhost(uint32_t x, uint32_t y, const uint16_t* image, uint8_t w, uint8_t h, status_t status){
	Character ghost = {x, y, 0, 1, 0, 0, w, h, image, image, status};
	return ghost;
}

void GhostDraw(){
	for(int i = 0; i < NumGhosts; i++){
		ST7735_DrawBitmap(GhostArray[i].x, GhostArray[i].y, GhostArray[i].image, GhostArray[i].w, GhostArray[i].h);
	}
}

void PlayerDraw(){
		ST7735_DrawBitmap(player.x, player.y, player.image, player.w, player.h);
}

void PlayerUpdate(uint8_t input){
	switch(input){
			case 0: // still
//				player.dx = 0;
//				player.dy = 0;
				break;
			case 1: // down
				player.dx = 0;
				player.dy = 1;
				break;
			case 2: // right
				player.dx = 1;
				player.dy = 0;
				break;
			case 4: // left
				player.dx = -1;
				player.dy = 0;
				break;
			case 8: // up
				player.dx = 0;
				player.dy = -1;
				break;
		}
}

void Erase(Character c){
	ST7735_DrawBitmap(c.x, c.y, c.erase, c.w, c.h);
}

void PlayerMove(){
//	Erase(player);
//	uint32_t position = 128 * ADC_In() / 4096;
//	position = 128 * position / 4096;
//	player.x = position;
		player.x += player.dx;
		player.y += player.dy;
}

void GhostMove(){
	for(int i = 0; i < NumGhosts; i++){
		GhostArray[i].x += GhostArray[i].dx;
		GhostArray[i].y += GhostArray[i].dy;
	}
}

void WorldDraw(){
	//GhostDraw();
	PlayerDraw();
}

void WorldMove(){
//	GhostMove();
	PlayerMove();
}

uint32_t time = 0;
volatile uint32_t flag;
void nextFrame(void){
	time++;
	WorldMove();
  flag = 1; // semaphore
}
void clock(void){
  // doing nothing rn
}

void GameInit(){
	ST7735_DrawBitmap(0, 159, complete_map_pacman, 128, 160);
	// init sprites
	for(int i = 0; i < NumGhosts; i++){
		GhostArray[i] = CreateGhost(20 * i, 20, SmallEnemy10pointA, 16, 10, alive);
	}
}

int main(void){
	DisableInterrupts();
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  // TExaS_Init();
  Random_Init(1);
  Output_Init();
	ST7735_SetRotation(2);
	ADC_Init();
  Timer0_Init(&nextFrame,80000000/30); // 60 Hz
  Timer1_Init(&clock,80000000); // 1 Hz
	EdgeTrigger_Init(&PlayerUpdate);
  GameInit();
	EnableInterrupts();
	int count = 0;
  while(1){
//		if((GPIO_PORTE_DATA_R & 0xF) != 0) count++;
		ST7735_SetCursor(0, 0);
		ST7735_OutChar(' ');
		ST7735_OutChar(' ');
		ST7735_OutChar(' ');
		ST7735_SetCursor(0, 0);
		uint32_t period = 128 * ADC_In() / 4096;
		ST7735_OutUDec(period);
    while(flag==0){};
    flag = 0;
		WorldDraw();
  }
}




