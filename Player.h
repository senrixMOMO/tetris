#pragma once
#include <vector>
#include <memory>
#include "VECTOR2.h"
#include "GameBoard.h"

#define BLOCK_SIZE 25

enum BLOCK
{
	BL_T,
	BL_L,
	BL_J,
	BL_Z,
	BL_S,
	BL_I,
	BL_O,
	BL_MAX
};


struct Block {
	std::vector<std::vector<VECTOR2>> pos;
	bool flag;
	int RotaCnt;
	int color;
};

class Player
{
public:
	Player(std::weak_ptr<GameBoard> gb);
	~Player();

	int SetMove(void);
	void Draw(void);

	Block Btype[BL_MAX];
	Block playblock;
	Block Nextplayblock;
	BLOCK block;

	void init(void);
private:
	Block Random(void);
	int time;
	int img[7];
	char keyData[256];
	char keyDataOld[256];
	std::shared_ptr<GameBoard> gb;

};

