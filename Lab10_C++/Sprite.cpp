#include "stdint.h"
#include "Images.h"
#include "ST7735.h"
#include "Sprite.h"

Sprite::Sprite(int x, int y, const uint16_t** alive, uint8_t aliveCount,
			 const uint16_t** death, uint8_t deathCount, const uint16_t *erase,
			 uint8_t w, uint8_t h, status_t status){
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->prevx = x;
	this->prevy = y;
	this->w = w;
	this->h = h;
	this->dir = right;
	this->nextDir = dir;
	this->alive = alive;
	this->aliveCount = aliveCount;
	this->death = death;
	this->deathCount = deathCount;
	this->status = status;
	this->type = player;
}
			 
Sprite::Sprite(int32_t xPos, int32_t yPos, const uint16_t** img){
		x = xPos;
		y = yPos;
		w = 9;
		h = 9;
		alive = img;
		aliveCount = 0;
		status = idle;
		dir = up;
		type = ghost;
}

void Sprite::Draw(){
	static uint8_t count = 0;
	static uint8_t index = 0;
	static uint8_t deathIndex = 0;
	if(status == active || status == idle){
		ST7735_DrawBitmap(x, y, alive[index % aliveCount], w, h);
		count++;
		if(count > 50){
			index++;
			count = 0;
		}
	}else if(status == dying){
		index = 0;
		ST7735_DrawBitmap(x, y, death[deathIndex % deathCount], w, h);
		for(int i = 0; i < 2000000; i++);
		deathIndex++;
		if(deathIndex == deathCount){
			status = dead;
			deathIndex = 0;
		}
	}
}

dir_t Sprite::RedGhostDir(int32_t pacX, int32_t pacY){
		int32_t deltaX = x - pacX;
		int32_t deltaY = y - pacY;
	
		int32_t absDeltaX = deltaX < 0 ? deltaX * -1 : deltaX;
		int32_t absDeltaY = deltaY < 0 ? deltaY * -1 : deltaY;
	
		int32_t maxInt32Val = 2147483647;
		int32_t one = maxInt32Val, two = maxInt32Val, three = maxInt32Val;
	
		if(CanMove((dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4))) one = Distance(pacX, pacY, (dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4));
		if(CanMove((dir_t)(((int)dir - 0) % 4))) two = Distance(pacX, pacY, (dir_t)(((int)dir - 0) % 4));
		if(CanMove((dir_t)(((int)dir + 1) % 4))) three = Distance(pacX, pacY, (dir_t)(((int)dir + 1) % 4));
	
		this->dir = findMin(one, two, three);
		this->nextDir = dir;
}
dir_t Sprite::PinkGhostDir(int32_t pacX, int32_t pacY, dir_t pacDir){
	if(pacDir == left){
		return RedGhostDir(pacX - 10, pacY);
	} else if(pacDir == right){
		return RedGhostDir(pacX + 10, pacY);
	} else if(pacDir == up){
		return RedGhostDir(pacX, pacY - 10);
	} else if(pacDir == down){
		return RedGhostDir(pacX, pacY + 10);
	}
}
dir_t Sprite::BlueGhostDir(int32_t pacX, int32_t pacY, dir_t pacDir, int32_t redX, int32_t redY){
		int32_t pinkTargetX;
		int32_t pinkTargetY;
		if(pacDir == left){
			int32_t pinkTargetX = pacX - 10;
			int32_t pinkTargetY = pacY;
		} else if(pacDir == right){
			int32_t pinkTargetX = pacX + 10;
			int32_t pinkTargetY = pacY;
		} else if(pacDir == up){
			int32_t pinkTargetX = pacX;
			int32_t pinkTargetY = pacY - 10;
		} else if(pacDir == down){
			int32_t pinkTargetX = pacX;
			int32_t pinkTargetY = pacY + 10;
		}
		int32_t blueTargetX = (2*(redX - pinkTargetX)) + pinkTargetX;
		int32_t blueTargetY = (2*(redY - pinkTargetY)) + pinkTargetY;
		
		return RedGhostDir(blueTargetX, blueTargetY);
}
dir_t Sprite::YellowGhostDir(int32_t pacX, int32_t pacY){
		
		int32_t deltaX = x - pacX;
		int32_t deltaY = y - pacY;

		deltaX = deltaX < 0 ? deltaX - 20 : deltaX + 20;
		deltaY = deltaY < 0 ? deltaY - 20 : deltaY + 20;
	
		int32_t absDeltaX = deltaX < 0 ? deltaX * -1 : deltaX;
		int32_t absDeltaY = deltaY < 0 ? deltaY * -1 : deltaY;
	
		int32_t maxInt32Val = 2147483647;
		int32_t one = maxInt32Val, two = maxInt32Val, three = maxInt32Val;
	
		if(CanMove((dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4))) one = Distance(pacX, pacY, (dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4));
		if(CanMove((dir_t)(((int)dir - 0) % 4))) two = Distance(pacX, pacY, (dir_t)(((int)dir - 0) % 4));
		if(CanMove((dir_t)(((int)dir + 1) % 4))) three = Distance(pacX, pacY, (dir_t)(((int)dir + 1) % 4));
	
		this->dir = findMin(one, two, three);
		this->nextDir = dir;
}

void Sprite::Erase(){
	ST7735_DrawBitmap(x, y, black9x9, w, h);
}

bool Sprite::isCollision(int pacx, int pacy){
	int centerX = x + w/2;
	int centerY = y - h/2;
	
	int xDiff = centerX - pacx;
	if(xDiff < 0) xDiff *= -1;
	int yDiff = centerY - pacy;
	if(yDiff < 0) yDiff *= -1;
	
	return (xDiff > yDiff ? xDiff : yDiff) < 8;
}
bool Sprite::getColor(int x, int y){
	return map_pacman[x + (159 - y) * 128] != 0x0000;
}

bool Sprite::isHorizontalWall(int x, int y, uint8_t dim){
	if(x < 0 || x > 127) return true;
	for(int i = x; i < x + dim; i++){
		if(getColor(i, y)) return true;
	}
	return false;
}
bool Sprite::isVerticalWall(int x, int y, uint8_t dim){
	if(x < 0 || x > 127) return false;
	for(int i = y; i < y + dim; i++){
		if(getColor(x, i)) return true;
	}
	return false;
}

bool Sprite::CanMove(dir_t d){
	if(d == up){
		return !isHorizontalWall(x, y - h, w);
	}else if(d == down){
		return !isHorizontalWall(x, y + 1, w);
	}else if(d == left){
		return !isVerticalWall(x - 1, y - h + 1, w);
	}else if(d == right){
		return !isVerticalWall(x + w, y - h + 1, w);
	}
}

int32_t Sprite::Distance(int32_t pacX, int32_t pacY, dir_t ghostDir){
    int32_t deltaX = (pacX - this->x);
    int32_t deltaY = (pacY - this->y);

    int32_t dLeft = pacX - (this->x - 1);
    int32_t dRight = pacX - (this->x + 1);
    int32_t dUp = pacY - (this->y - 1);
    int32_t dDown = pacY - (this->y + 1);

    if(ghostDir == left){
        return (dLeft * dLeft) + (deltaY * deltaY);
    } else if(ghostDir == right){
        return (dRight * dRight) + (deltaY * deltaY);
    } else if(ghostDir == up){
        return (deltaX * deltaX) + (dUp * dUp);
    } else {
        return (deltaX * deltaX) + (dDown * dDown);
    }
}

dir_t Sprite::findMin(int32_t d1, int32_t d2, int32_t d3){
    if(d1 <= d2 && d1 <= d3){
        return (dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4);
    } else if(d2 <= d1 && d2 <= d3){
        return this->dir;
    } else {
        return (dir_t)((dir + 1) % 4);
    }
}

dir_t Sprite::GhostDir(int pacX, int pacY){
	int32_t deltaX = x - pacX;
	int32_t deltaY = y - pacY;
	
	int32_t absDeltaX = deltaX < 0 ? deltaX * -1 : deltaX;
	int32_t absDeltaY = deltaY < 0 ? deltaY * -1 : deltaY;
	
	int32_t maxInt32Val = 2147483647;
	int32_t one = maxInt32Val, two = maxInt32Val, three = maxInt32Val;
	
	if(CanMove((dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4))) one = Distance(pacX, pacY, (dir_t)((((int)dir - 1) < 0 ? (dir_t) 3 : ((int)dir - 1)) % 4));
	if(CanMove((dir_t)(((int)dir - 0) % 4))) two = Distance(pacX, pacY, (dir_t)(((int)dir - 0) % 4));
	if(CanMove((dir_t)(((int)dir + 1) % 4))) three = Distance(pacX, pacY, (dir_t)(((int)dir + 1) % 4));
	
	this->dir = findMin(one, two, three);
	this->nextDir = dir;
}
void Sprite::Update(uint8_t input){
	if(status == active){
		if(input == 8){
			nextDir = up;
		}else if(input == 1){
			nextDir = down;
		}else if(input == 4){
			nextDir = left;
		}else if(input == 2){
			nextDir = right;
		}
	}
}
void Sprite::UpdateDir(){
	dir = nextDir;
}
void Sprite::UpdateOrientation(){
	if(dir == up){
		alive[0] = pacman_open_up;
	}else if(dir == down){
		alive[0] = pacman_open_down;
	}else if(dir == left){
		alive[0] = pacman_open_left;
	}else if(dir == right){
		alive[0] = pacman_open_right;
	}
}
void Sprite::Move(){
	if(CanMove(nextDir)) UpdateDir();
	if(CanMove(dir)){
		if(dir == up){
			y--;
		}else if(dir == down){
			y++;
		}else if(dir == left){
			x--;
		}else if(dir == right){
			x++;
		}
	}
	if(x <= -w){
		x = 127;
	}else if(x >= 128){
		x = -w + 1;
	}
}
