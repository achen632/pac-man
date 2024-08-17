#include "stdint.h"
#include "Images.h"
#include "ST7735.h"

#define NumGhosts 4
typedef enum {dead, active, idle, dying} status_t;
typedef enum {up, right, down, left} dir_t;
typedef enum {player, ghost} type_t;

class Sprite{
	public:
		int x;
		int y;
		int8_t dx;
		int8_t dy;
		int prevx;
		int prevy;
		uint8_t w;
		uint8_t h;
		dir_t dir;
		dir_t nextDir;
		const uint16_t** alive;
		uint8_t aliveCount;
		const uint16_t** death;
		uint8_t deathCount;
		status_t status;
		type_t type;
		Sprite(int x, int y, const uint16_t** alive, uint8_t aliveCount, const uint16_t** death, uint8_t deathCount, const uint16_t *erase, uint8_t w, uint8_t h, status_t status);
		Sprite(int x, int y, const uint16_t** img);
		void Draw();
		void Update(uint8_t input);
		void Erase();
		bool CanMove(dir_t d);
		void UpdateDir();
		void Move();
		int32_t Distance(int32_t pacX, int32_t pacY, dir_t ghostDir);
		dir_t findMin(int32_t d1, int32_t d2, int32_t d3);
		bool getColor(int x, int y);
		bool isVerticalWall(int x, int y, uint8_t dim);
		bool isHorizontalWall(int x, int y, uint8_t dim);
		void MoveGhost(int32_t pacX, int32_t pacY);		
		dir_t GhostDir(int32_t pacX, int32_t pacY);
		void UpdateOrientation();
		bool isCollision(int pacx, int pacy);
		dir_t RedGhostDir(int32_t pacX, int32_t pacY);
		dir_t PinkGhostDir(int32_t pacX, int32_t pacY, dir_t pacDir);
		dir_t BlueGhostDir(int32_t pacX, int32_t pacY, dir_t pacDir, int32_t redX, int32_t redY);
		dir_t YellowGhostDir(int32_t pacX, int32_t pacY);
};
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
