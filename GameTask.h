#pragma once
#include <mutex>
#include <memory>
#include <list>
#include <chrono>
#include "VECTOR2.h"
#include "Player.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 700

#define lpGameTsk GameTask::GetInstance()

enum GMODE
{
	GMODE_SYS_INIT,
	GMODE_TITLE,
	GMODE_GAME_INIT,
	GMODE_GAME_MAIN,
	GMODE_RESULT,
	GMODE_MAX
};


class GameBoard;

class GameTask
{
public:
	static void Create();
	static void Destroy();
	static GameTask &GetInstance()
	{
		Create();
		return *s_Instance;
	}
	int Update(void);

	char keyData[256];
	char keyDataOld[256];

private:
	GameTask();
	~GameTask();

	int SysInit(void);
	int Title(void);
	int GameInit(void);
	int GameMain(void);
	int Result(void);
	int SysDestroy(void);

	VECTOR2 drawOffset;
	GMODE mode;

	int(GameTask::*GtskTbl[GMODE_MAX])(void);
	std::shared_ptr<GameBoard> gb;
	std::unique_ptr<Player> player;

	static GameTask *s_Instance;
	int image;
	int DrawCnt;
protected:
};

