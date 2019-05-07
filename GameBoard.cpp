#include "GameBoard.h"
#include "Dxlib.h"



GameBoard::GameBoard()
{
	boardLT = VECTOR2(262, 75);
	SetBoard();
	WaitCnt = 0;
	flag = false;
	Score = 0;
}

GameBoard::GameBoard(VECTOR2 vec)
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::Draw(void)
{
	DrawBox(boardLT.x, boardLT.y, 300 + boardLT.x, 550 + boardLT.y, GetColor(255, 255, 255), true);
	DrawBox(25 + boardLT.x, 25 + boardLT.y, 275 + boardLT.x, 525 + boardLT.y, 0x808080, true);
	DrawBox(600, boardLT.y, 770, 190, 0x808080, true);
	DrawBlock();

	DrawString(600, 400, "SCORE", 0xffffff);
	int drawLength = GetDrawFormatStringWidth("%d", Score);
	DrawFormatString(750 - drawLength, 525, 0xffffff, "%d", Score);
}

void GameBoard::DrawScore(void)
{
}

void GameBoard::Update(void)
{
	WaitCnt--;
	DeleteBlock();
	DownBlock();
}

void GameBoard::SetBoard(void)
{
	DxLib::LoadDivGraph("image/blocks.png", 7, 7, 1, 25, 25, img, true);
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			board[i][j] = -1;
		}
	}
}

void GameBoard::DrawBlock()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (board[i][j]>=0)
			{
				DrawGraph((j+1) * 25 + boardLT.x, (i+1) * 25 + boardLT.y,img[board[i][j]], true);
			}
		}
	}
}

//　あたり判定
//　pos:配列の座標
bool GameBoard::Hitcheck(VECTOR2 pos)
{
	bool rtnFlg = false;

	if (pos.y >= 0 && pos.y < BOARD_HEIGHT)
	{
		if (pos.x >= 0 && pos.x < BOARD_WIDTH)
		{
			if (board[pos.y][pos.x] == -1)
			{
				rtnFlg = true;
			}
		}
	}
	return rtnFlg;
}

void GameBoard::DeleteBlock(void)
{	
	int dely = -1;
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		int Cnt = 0;
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (board[y][x]>=0)
			{
				Cnt++;
			}
			if (Cnt == BOARD_WIDTH)
			{
				dely = y;
				if (!flag)
				{
					WaitCnt = 30;
					flag = true;
				}
			}
		}
	}

	if (flag&&(WaitCnt<=0))
	{
		for (int delx = 0; delx < BOARD_WIDTH; delx++)
		{
			board[dely][delx] = -1;
			Score += 10;
		}
		flag = false;
	}
}

void GameBoard::DownBlock(void)
{
	for (int y = 1; y < BOARD_HEIGHT; y++)
	{
		int Cnt = 0;
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (board[y][x]==-1)
			{
				Cnt++;
			}
			if (Cnt == BOARD_WIDTH)
			{
				for (int delx = 0; delx < BOARD_WIDTH; delx++)
				{
					board[y][delx] = board[y - 1][delx];
					board[y - 1][delx] = -1;
				}
			}
		}
	}
}

void GameBoard::WriteBlock(VECTOR2 pos,int color)
{
	board[pos.y][pos.x] = color;
}
