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
#include "string"
#include "Sprite.h"
#include "Food.h"
#include "Sound.h"

#define FrameRate 240
extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);
using namespace std;

// Pac-Man
const uint16_t* pacAlive[] = {pacman_open_right, pacman_close};
const uint16_t* pacDeath[] = {pacman_close, pacman_dying1, pacman_dying2, pacman_dying3, black9x9};
Sprite pac = Sprite(59, 104, pacAlive, 2, pacDeath, 5, black9x9, 9, 9, idle);

// Ghosts
const uint16_t* red[1] = {red_ghost};
const uint16_t* pink[1] = {pink_ghost};
const uint16_t* yellow[1] = {yellow_ghost};
const uint16_t* blue[1] = {blue_ghost};
Sprite Ghosts[NumGhosts] = {Sprite(59, 79, red, 1, pacDeath, 5, black9x9, 9, 9, active), 
														Sprite(59, 92, pink, 1, pacDeath, 5, black9x9, 9, 9, idle), 
														Sprite(68, 92, yellow, 1, pacDeath, 5, black9x9, 9, 9, idle), 
														Sprite(50, 92, blue, 1, pacDeath, 5, black9x9, 9, 9, idle)};
//Ghost Ghosts[NumGhosts] = {Ghost(59, 79, red_ghost), 
//														Ghost(59, 92, pink_ghost), 
//														Ghost(68, 92, yellow_ghost), 
//														Ghost(50, 92, blue_ghost)};

// Food
Food FoodArray[FoodNum] = {
        Food(11, 27),
        Food(19, 27),
        Food(26, 27),
        Food(34, 27),
        Food(42, 27),
        Food(51, 27),
        Food(76, 27),
        Food(85, 27),
        Food(93, 27),
        Food(101, 27),
        Food(108, 27),
        Food(116, 27),

        Food(11, 35),
        Food(51, 35),
        Food(76, 35),
        Food(116, 35),

        Food(11, 43),
        Food(19, 43),
        Food(26, 43),
        Food(34, 43),
        Food(42, 43),
        Food(51, 43),
        Food(59, 43),
        Food(68, 43),
        Food(76, 43),
        Food(85, 43),
        Food(93, 43),
        Food(101, 43),
        Food(108, 43),
        Food(116, 43),

        Food(11, 52),
        Food(42, 52),
        Food(85, 52),
        Food(116, 52),

        Food(42, 61),
        Food(51, 61),
        Food(76, 61),
        Food(85, 61),

        Food(11, 63),
        Food(24, 63),
        Food(103, 63),
        Food(116, 63),

        Food(24, 71),
        Food(103, 71),

        Food(42, 75),
        Food(51, 75),
        Food(59, 75),
        Food(68, 75),
        Food(76, 75),
        Food(85, 75),

        Food(24, 79),
        Food(103, 79),

        Food(6, 88),
        Food(15, 88),
        Food(24, 88),
        Food(33, 88),
        Food(42, 88),
        Food(85, 88),
        Food(94, 88),
        Food(103, 88),
        Food(112, 88),
        Food(121, 88),

        Food(24, 100),
        Food(42, 100),
        Food(51, 100),
        Food(76, 100),
        Food(85, 100),
        Food(103, 100),

        Food(11, 113),
        Food(17, 113),
        Food(24, 113),
        Food(33, 113),
        Food(42, 113),
        Food(85, 113),
        Food(94, 113),
        Food(103, 113),
        Food(110, 113),
        Food(116, 113),

        Food(11, 120),
        Food(116, 120),

        Food(11, 127),
        Food(28, 127),
        Food(35, 127),
        Food(42, 127),
        Food(51, 127),
        Food(59, 127),
        Food(68, 127),
        Food(76, 127),
        Food(85, 127),
        Food(92, 127),
        Food(99, 127),
        Food(116, 127),

        Food(11, 134),
        Food(28, 134),
        Food(51, 134),
        Food(76, 134),
        Food(99, 134),
        Food(116, 134),

        Food(11, 141),
        Food(28, 141),
        Food(51, 141),
        Food(76, 141),
        Food(99, 141),
        Food(116, 141),

        Food(11, 148),
        Food(19, 148),
        Food(28, 148),
        Food(36, 148),
        Food(43, 148),
        Food(51, 148),
        Food(59, 148),
        Food(68, 148),
        Food(76, 148),
        Food(84, 148),
        Food(91, 148),
        Food(99, 148),
        Food(108, 148),
        Food(116, 148)
};




// Constants
typedef enum {eng, spn} language_t;
language_t lang;
uint32_t score = 0, flag = 0, play = 0;
uint8_t spawnCount, spawnIndex;

void LED_Init(){ // PD0 Green, PD1 Red, PD6 Blue
	SYSCTL_RCGCGPIO_R |= 0x8;
	__nop();
	__nop();
	GPIO_PORTD_DEN_R |= 0x3;
	GPIO_PORTD_DIR_R |= 0x3;
	GPIO_PORTD_DATA_R |= 0x1;
}
void LED_Toggle(){
	static int count = 0;
	if(count % 10 == 0){
		GPIO_PORTD_DATA_R ^= 0x1;
	}
	count++;
}
void RegenItems(){
	pac = Sprite(59, 104, pacAlive, 2, pacDeath, 5, black9x9, 9, 9, idle);
	pac.alive[0] = pacman_open_right;
	Ghosts[0] = Sprite(59, 79, red, 1, pacDeath, 5, black9x9, 9, 9, active);
	Ghosts[1] = Sprite(59, 92, pink, 1, pacDeath, 5, black9x9, 9, 9, idle);
	Ghosts[2] = Sprite(68, 92, yellow, 1, pacDeath, 5, black9x9, 9, 9, idle);
	Ghosts[3] = Sprite(50, 92, blue, 1, pacDeath, 5, black9x9, 9, 9, idle);
	for(int i = 0; i < FoodNum; i++){
		FoodArray[i].isThere = true;
	}
}
void DrawFood(void){
  for(int i = 0; i < FoodNum; i++){
    if(FoodArray[i].isThere){  
      ST7735_DrawPixel(FoodArray[i].x, FoodArray[i].y, 0xFFE0);
    }
  }
}

void GameOver(){
	pac.status = dead;
	if(lang == eng){
		int x = 6;
		int y = 8;
		if(score == 118){
			ST7735_DrawString(x, y, "You Win!", ST7735_YELLOW);
		}else{
			ST7735_DrawString(x, y, "Game Over!", ST7735_YELLOW);
		}
		ST7735_SetCursor(x, y + 1);
		ST7735_OutString("Score: ");
		ST7735_OutUDec(score);
	}else{
		int x = 4;
		int y = 8;
		if(score == 118){
			ST7735_DrawString(x, y, "Tú Ganaste!", ST7735_YELLOW);			
		}else{
			ST7735_DrawString(x, y, "Juego Terminado!", ST7735_YELLOW);
		}		
		ST7735_SetCursor(x, y + 1);
		ST7735_OutString("Puntaje: ");
		ST7735_OutUDec(score);
	}
	endSound();
	play = 2;
}							
void KillPac(){
	pac.status = dying;
}

void spawn(void){
	if(play == 1 && pac.status == active){
		if(spawnCount > 75 && spawnIndex < NumGhosts){
			Ghosts[spawnIndex].status = active;
			Ghosts[spawnIndex].Erase();
			Ghosts[spawnIndex].x = 59;
			Ghosts[spawnIndex].y = 79;
			Ghosts[spawnIndex].Draw();
			spawnIndex++;
			spawnCount = 0;
		}
		spawnCount++;
	}
}

void GameStart(){
	ST7735_DrawBitmap(0, 42, replace_toplogo, 128, 43);
	ST7735_DrawBitmap(15, 75, replace_engl, 36, 14);
	ST7735_DrawBitmap(77, 75, replace_span, 36, 14);
	ST7735_DrawBitmap(10, 139, replace_difficulty, 108, 14);
	ST7735_DrawBitmap(10, 126, replace_select_difficulty, 108, 14);
	DrawFood();
	ST7735_SetCursor(0, 0);
	ST7735_OutUDec(score);
	SetSound(Sound_Chomp);
	pac.status = active;
	play = 1;
}

void DrawSpan(){
	ST7735_DrawBitmap(15, 75, engl, 36, 14);
	ST7735_DrawBitmap(77, 75, span_selected, 36, 14);
	ST7735_DrawBitmap(10, 126, selectDifficulty_span, 108, 14);
}

void DrawEngl(){
	ST7735_DrawBitmap(15, 75, engl_selected, 36, 14);
	ST7735_DrawBitmap(77, 75, span, 36, 14);
	ST7735_DrawBitmap(10, 126, selectDifficulty_engl, 108, 14);
}


void GameInit(){
	LED_Init();
	ST7735_DrawBitmap(0, 159, map_pacman, 128, 160);
	ST7735_DrawBitmap(10, 139, difficulty_blend, 108, 14);
	ST7735_DrawBitmap(0, 42, title_logo_pacman, 128, 43);
	spawnIndex = 1;
	spawnCount = 0;
	DrawEngl();
	pac.Draw();
	for(int i = 0; i < NumGhosts; i++){
		Ghosts[i].Draw();
	}
	SetSound(Sound_Begin);
}

void UpdateMenu(uint8_t x){
	if(x == 2){ // right
		DrawSpan();
		lang = spn;
	}else if(x == 4){ // left
		DrawEngl();
		lang = eng;
	}else if(x == 8 || x == 1){ // up or down
		GameStart();
	}
}


void reset(){
	RegenItems();
	GameInit();
	score = 0;
	play = 0;
}

void Update(uint8_t x){
	if(play == 0){
		UpdateMenu(x);
	}else if(play == 1){
		pac.Update(x);
	}else if(play == 2){
		reset();
	}
}

void UpdateJoy(){
		uint32_t x[2] = {};
		ADC_JoyIn(x);
		if(x[1] > 2500){ // left
			Update(4);
		}else if(x[1] < 1500){ // right
			Update(2);
		}else if(x[0] > 2500){ // up
			Update(8);
		}else if(x[0] < 1500){ // down
			Update(1);
		}
}
void refresh(void){
	spawn();
	if(pac.status == active){
		pac.Move();
		pac.UpdateOrientation();
		static uint8_t slow = 0;
		if(slow % 2 == 0){
//			for(int i = 0; i < NumGhosts; i++){
//				if(Ghosts[i].status == active){
//					Ghosts[i].GhostDir(pac.x, pac.y);
//					Ghosts[i].Move();
//				}
//			}
			Ghosts[0].RedGhostDir(pac.x, pac.y);
			Ghosts[0].Move();
			Ghosts[1].PinkGhostDir(pac.x, pac.y, pac.dir);
			Ghosts[1].Move();
			Ghosts[2].YellowGhostDir(pac.x, pac.y);
			Ghosts[2].Move();
			Ghosts[3].BlueGhostDir(pac.x, pac.y, pac.dir, Ghosts[0].x, Ghosts[0].y);
			Ghosts[3].Move();
		}
		slow++;
	}
	flag = 1;
}
void SystemInit(){
	DisableInterrupts();
  PLL_Init(Bus80MHz);
  Output_Init();
	Sound_Init();
	ST7735_SetRotation(2);
	ADC_Init();
  Timer0_Init(&refresh, 80000000/FrameRate); // 60 Hz
	EdgeTrigger_Init(&Update);
	GameInit();
	EnableInterrupts();
}




void DrawGame(){
	LED_Toggle();
	pac.Draw();
	if(pac.status == active){
		for(int i = 0; i < FoodNum; i++){
			if(FoodArray[i].checkFoodCollision(pac.x, pac.y)){
				score++;
				ST7735_SetCursor(0, 0);
				ST7735_OutUDec(score);
				if(score == FoodNum) GameOver();
			}
		}
		DrawFood();
		for(int i = 0; i < NumGhosts; i++){
			Ghosts[i].Draw();
			if(Ghosts[i].isCollision(pac.x + pac.w/2, pac.y - pac.h/2) && pac.status != dead){
				endSound();
				pac.status = dying;
				for(int i = 0; i < 10000000; i++);
				for(int i = 0; i < NumGhosts; i++){
					Ghosts[i].Erase();
				}
				pac.Draw();
				SetSound(Sound_Death);
				break;
			}
		}
	}
}
int main(void){
	SystemInit();
	while(1){
		while(play == 0){
			UpdateJoy();
		}
		while(play == 1){
			while(flag == 0){}
			flag = 0;
			UpdateJoy();
			DrawGame();
			if(pac.status == dead){
				while(notFinished()){}
				GameOver();
			}
		}
		while(play == 2){
			UpdateJoy();
		}
	}
}
