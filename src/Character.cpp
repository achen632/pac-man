#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"

typedef enum {dead,alive} status_t;
class Character{
public:
	uint32_t x;      // x coordinate
  uint32_t y;      // y coordinate
	int8_t dx;      // dx
  int8_t dy;      // dy
  uint32_t prevx;
  uint32_t prevy;
	uint8_t w;
	uint8_t h;
	const uint16_t *image; // ptr->image
  status_t life;            // dead/alive

	Character(uint32_t x, uint32_t y, uint8_t w, uint8_t h, const uint16_t *image, status_t life){
		this->y = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->image = image;
		this->life = life;
		this->dx = 0;
		this->dy = 0;
		prevx = x;
		prevy = y;
	}

	void Draw(){
		ST7735_DrawBitmap(x, y, image, w, h);
	}

	void Move(){
		x += dx;
		y += dy;
	}

	void Update(uint8_t input){
		switch(input){
			case 0: // up
				dx = 0;
				dy = -1;
				break;
			case 1: // right
				dx = 1;
				dy = 0;
				break;
			case 2: // down
				dx = 0;
				dy = 1;
				break;
			case 3: // left
				dx = -1;
				dy = 0;
				break;
		}
	}
};
