#include "stdint.h"
//#include "Sprite.h"

class Ghost{
public:
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    const uint16_t *image;
    dir_t dir;
    Ghost(int32_t xPos, int32_t yPos, const uint16_t *img);
    dir_t ghostDir(int32_t pacX, int32_t pacY);
		void Draw();
    void moveGhost(dir_t dir);
};