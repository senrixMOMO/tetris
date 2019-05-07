#include"DxLib.h"
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameTask::Create();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().Update();
	}
	DxLib_End();

	return 0;				// ソフトの終了 
}
