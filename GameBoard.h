#pragma once
#include <list>
#include <memory>
#include <vector>
#include "VECTOR2.h"

#define BOARD_WIDTH (10)
#define BOARD_HEIGHT (20)

class GameBoard
{
public:
	GameBoard();
	GameBoard(VECTOR2 vec);
	~GameBoard();

	void Draw(void);
	void DrawScore(void);
	void Update(void);
	void SetBoard(void);
	void DrawBlock();
	bool Hitcheck(VECTOR2 pos);
	void DeleteBlock(void);
	void DownBlock(void);
	void WriteBlock(VECTOR2 pos,int color);
	int GetWaitCnt() { return WaitCnt; };

	VECTOR2 boardSize;		//î’ñ ÇÃêî
	VECTOR2 boardLT;		//offset
private:
	int img[7];
	int WaitCnt;
	int board[BOARD_HEIGHT][BOARD_WIDTH];
	bool flag;
	int Score;
};

