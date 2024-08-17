#include <stdint.h>
#define FoodNum 118

class Food{
	public:
    int16_t x;
    int16_t y;
    bool isThere;
    Food(int16_t xpos, int16_t ypos);
    bool checkFoodCollision(int32_t objX, int32_t objY);
};
