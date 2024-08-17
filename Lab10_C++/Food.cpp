#include <stdint.h>
#include "Food.h"

Food::Food(int16_t xpos, int16_t ypos){
	x = xpos;
	y = ypos;
	isThere = true;
}
bool Food::checkFoodCollision(int32_t objX, int32_t objY){
	if(isThere && ((((int16_t)objX + 0) < this->x) && (((int16_t)objX + 8) > this->x)) && ((((int16_t)objY - 0) > this->y) && (((int16_t)objY - 8) < this->y))){
			this->isThere = false;
		return true;
	}
	return false;
}
