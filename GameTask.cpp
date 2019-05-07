#include "GameTask.h"
#include "GameBoard.h"
#include "Player.h"
#include "DxLib.h"

GameTask *GameTask::s_Instance = nullptr;

GameTask::GameTask()
{
	DrawCnt = 0;
	mode = GMODE_SYS_INIT;
	GtskTbl[GMODE_SYS_INIT] = &GameTask::SysInit;
	GtskTbl[GMODE_TITLE] = &GameTask::Title;
	GtskTbl[GMODE_GAME_INIT] = &GameTask::GameInit;
	GtskTbl[GMODE_GAME_MAIN] = &GameTask::GameMain;
	GtskTbl[GMODE_RESULT] = &GameTask::Result;
	SetFontSize(30);
	ChangeFont("HGS創英角ﾎﾟｯﾌﾟ体");
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
}


GameTask::~GameTask()
{
}

void GameTask::Create()
{
	if (!s_Instance)
	{
		s_Instance = new GameTask();
	}
}

void GameTask::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

int GameTask::Update(void)
{
	int rtn_id;

	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);

	rtn_id = (this->*GtskTbl[mode])();

	return rtn_id;
}

int GameTask::SysInit(void)
{
	SetWindowText("1701303_安倍泉里");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);	// 画面ｻｲｽﾞ設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	image = LoadGraph("image/title.png", true);
	mode = GMODE_TITLE;
	return true;
}

int GameTask::Title(void)
{
	ClsDrawScreen();
	DrawGraph(90, 50, image, true);
	DrawCnt++;
	if ((DrawCnt / 30) % 2)
	{
		DrawString(270, 600, "press 'ENTER KEY '", GetColor(255, 255, 255));
	}
	ScreenFlip();
	if (keyData[KEY_INPUT_RETURN] && !keyDataOld[KEY_INPUT_RETURN])
	{
		mode = GMODE_GAME_INIT;
	}
	return true;
}

int GameTask::GameInit(void)
{
	gb = std::make_shared<GameBoard>();
	player = std::make_unique<Player>(gb);
	mode = GMODE_GAME_MAIN;
	return true;
}

int GameTask::GameMain(void)
{
	ClsDrawScreen();
	DrawString(35, 100, "～操作方法～", 0xfffff);
	DrawString(15, 200, "十字キーで移動", 0xfffff);
	DrawString(15, 250, "Zキーで回転", 0xfffff);
	gb->Draw();
	gb->Update();
	mode = (GMODE)player->SetMove();
	player->Draw();
	ScreenFlip();
	return true;
}

int GameTask::Result(void)
{
	ClsDrawScreen();
	gb->Draw();
	player->Draw();
	DrawCnt++;
	if ((DrawCnt / 30) % 2)
	{
		DrawString(220, 650, "ENTERキーでタイトルに戻る", 0xff0000);
	}
	ScreenFlip();
	if (keyData[KEY_INPUT_RETURN] && !keyDataOld[KEY_INPUT_RETURN])
	{
		mode = GMODE_TITLE;
	}
	return true;
}

int GameTask::SysDestroy(void)
{
	return 0;
}
