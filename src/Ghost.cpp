#include "stdint.h"
//#include "Ghost.h"
#include "Sprite.h"

Ghost::Ghost(int32_t xPos, int32_t yPos, const uint16_t *img){
		x = xPos;
		y = yPos;
		width = 9;
		height = 9;
		image = img;
		dir = up;
}
void Ghost::Draw(void){
    ST7735_DrawBitmap(x, y, image, width, height);
}
dir_t Ghost::ghostDir(int32_t pacX, int32_t pacY){
		int32_t deltaX = (((pacX - this->x)*1000)/128);
		int32_t deltaY = (((pacY - this->y)*1000)/160);
		if(deltaX > deltaY){
				if(deltaX > 0){
						return right;
				} else {
						return left;
				}
		} else {
				if(deltaY > 0){
						return down;
				} else {
						return up;
				}
		}
}
//Syntax: name.moveGhost(name.ghostDir);
void Ghost::moveGhost(dir_t dir){
		//
		// TODO:
		// this->x == -9 && this->y == 92		<-- left teleport
		// this->x == 128 && this->y == 92	<-- right teleport
		//

		static bool moveConstant = false;
		static dir_t tempDir = up;

		if(this->x == 7 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(7 < this->x && this->x < 24 && this->y == 152){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 24 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(24 < this->x && this->x < 47 && this->y == 152){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 47 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(47 < this->x && this->x < 72 && this->y == 152){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(72 < this->x && this->x < 96 && this->y == 152){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 96 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(96 < this->x && this->x < 112 && this->y == 152){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 112 && this->y == 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 112 && 117 < this->y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 112 && this->y == 117){
			if(dir == down){
				this->y += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(99 < this->x && this->x < 112 && this->y == 117){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 99 && this->y == 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(81 < this->x && this->x < 99 && this->y == 117){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 81 && this->y == 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 38 && this->y == 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(20 < this->x && this->x < 38 && this->y == 117){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 20 && this->y == 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(7 < this->x && this->x < 20 && this->y == 117){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 7 && this->y == 117){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 7 && 117 < this->y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 7 && this->y == 31){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 47 && this->y == 31){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 47 && this->y == 47){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 47){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == left){
				this->x -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 31){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 65){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 38 && this->y == 79){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 99 && this->y == 69){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 112 && this->y == 31){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 47 && this->y == 65){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 95 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 24 && this->y == 131){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 20 && this->y == 67){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 81 && this->y == 79){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 20 && this->y == 92){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			}
		} else if(this->x == 99 && this->y == 92){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			}
		} else if(this->x == 38 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 81 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 79){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 47 && this->y == 79){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 38 && this->y == 47){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 81 && this->y == 47){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 47 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 72 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 112 && this->y == 47){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 38 && this->y == 92){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 81 && this->y == 104){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 39 && this->y == 104){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 81 && this->y == 92){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 7 && this->y == 47){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 81 && this->y == 65){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 112 && this->y == 67){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = left;
			}
		} else if(this->x == 7 && this->y == 67){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 38 && this->y == 65){
			if(dir == right){
				this->x += 1; moveConstant = false;
			} else if(dir == up){
				this->y -= 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(24 < this->x && this->x < 96 && this->y == 131){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(38 < this->x && this->x < 81 && this->y == 79){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(7 < this->x && this->x < 47 && this->y == 31){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(71 < this->x && this->x < 112 && this->y == 31){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(7 < this->x && this->x < 112 && this->y == 47){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(-8 < this->x && this->x < 38 && this->y == 92){	// IMPORTANT LEFT TELEPORT EDGE
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(81 < this->x && this->x < 127 && this->y == 92){	// IMPORTANT RIGHT TELEPORT EDGE
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(38 < this->x && this->x < 81 && this->y == 104){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(7 < this->x && this->x < 20 && this->y == 67){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(99 < this->x && this->x < 112 && this->y == 67){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(38 < this->x && this->x < 47 && this->y == 65){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(72 < this->x && this->x < 81 && this->y == 65){
			if(dir == left){
				this->x -= 1; moveConstant = false;
			} else if(dir == right){
				this->x += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = right;
			}
		} else if(this->x == 24 && 131 < y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 47 && 131 < y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 72 && 131 < y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 95 && 131 < y && this->y < 152){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 38 && 79 < y && this->y < 131){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 81 && 79 < y && this->y < 131){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 99 && 67 < y && this->y < 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 20 && 67 < y && this->y < 117){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 7 && 31 < y && this->y < 67){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 112 && 31 < y && this->y < 67){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 47 && 31 < y && this->y < 47){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 72 && 31 < y && this->y < 47){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 38 && 47 < y && this->y < 65){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 81 && 47 < y && this->y < 65){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 47 && 65 < y && this->y < 79){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		} else if(this->x == 72 && 65 < y && this->y < 79){
			if(dir == up){
				this->y -= 1; moveConstant = false;
			} else if(dir == down){
				this->y += 1; moveConstant = false;
			} else {
				moveConstant = true; tempDir = down;
			}
		}
		if(moveConstant){
			if(tempDir == right){
				this->x += 1;
			} else if(tempDir == left){
				this->x -= 1;
			} else if(tempDir == down){
				this->y += 1;
			}
		}
}