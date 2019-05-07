#include "Player.h"
#include "Dxlib.h"

Player::Player(std::weak_ptr<GameBoard> gb)
{
	init();
	this->gb = gb.lock();
	DxLib::LoadDivGraph("image/blocks.png", 7, 7, 1, 25, 25, img, true);
	playblock = Random();
	Nextplayblock = Random();
}


Player::~Player()
{
}

int Player::SetMove(void)
{
	if (gb->GetWaitCnt()>=0)
	{
		return 3;
	}

	memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	GetHitKeyStateAll(keyData);
	time++;
	bool flag = false;
	int dir[4] = {-1,-1,-1,-1},cnt=0;

	if (playblock.pos.begin() == playblock.pos.end())
	{
		playblock = Random();
	}

	for (auto pos : playblock.pos[playblock.RotaCnt])
	{
		if (!gb->Hitcheck(pos))
		{
			return 4;
		}
	}

	if (keyData[KEY_INPUT_Z] && !keyDataOld[KEY_INPUT_Z])
	{
		cnt = 0;
		for (auto pos : playblock.pos[((playblock.RotaCnt+1)% playblock.pos.size())])
		{
			if ((gb->Hitcheck(pos)))
			{
				dir[cnt] = 4;
			}
			cnt++;
		}
		for (int i = 0;i<4;i++)
		{
			if ((dir[i]==4)&&(i==3))
			{
				playblock.RotaCnt = ++playblock.RotaCnt % playblock.pos.size();
			}
			else if (dir[i] != 4)
			{
				break;
			}
		}
	}
	else
	{
		for (auto pos : playblock.pos[playblock.RotaCnt])
		{
			if (keyData[KEY_INPUT_DOWN] && !keyDataOld[KEY_INPUT_DOWN])
			{
				if ((gb->Hitcheck(pos + VECTOR2(0, 1))))
				{
					dir[cnt] = 3;
				}
			}
			if (keyData[KEY_INPUT_RIGHT] && !keyDataOld[KEY_INPUT_RIGHT])
			{
				if ((gb->Hitcheck(pos + VECTOR2(1, 0))))
				{
					dir[cnt] = 1;
				}
			}
			if (keyData[KEY_INPUT_LEFT] && !keyDataOld[KEY_INPUT_LEFT])
			{
				if ((gb->Hitcheck(pos + VECTOR2(-1, 0))))
				{
					dir[cnt] = 2;
				}
			}
			if (!((time) % 30))
			{
				if ((gb->Hitcheck(pos + VECTOR2(0, 1))))
				{
					dir[cnt] = 3;
				}
				else
				{
					flag = true;
				}
			}
			cnt++;
		}
	}
	

	if (flag == true)
	{
		for (auto& pos : playblock.pos[playblock.RotaCnt])
		{
			gb->WriteBlock(pos, playblock.color);
		}
		playblock.pos.clear();
		playblock = Nextplayblock;
		Nextplayblock = Random();
	}
	cnt = 0;
	for (int j = 0;j<playblock.pos.size();j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (dir[i] == -1)
			{
				return 3;
			}
		}
		for (auto &pos : playblock.pos[j])
		{
			switch (dir[cnt])
			{
			case 0:
				break;
			case 1:
				pos.x++;
				break;
			case 2:
				pos.x--;
				break;
			case 3:
				pos.y++;
				break;
			default:
				break;
			}
		}
		cnt++;
	}
	return 3;
}

void Player::Draw(void)
{
	for (auto pos : playblock.pos[playblock.RotaCnt])
	{
		DrawGraph((pos.x + 1) * BLOCK_SIZE + gb->boardLT.x, (pos.y + 1) * BLOCK_SIZE + gb->boardLT.y, img[playblock.color], true);
	}

	for (auto pos : Nextplayblock.pos[Nextplayblock.RotaCnt])
	{
		DrawGraph((pos.x + 15) * BLOCK_SIZE + gb->boardLT.x, (pos.y + 1) * BLOCK_SIZE + gb->boardLT.y, img[Nextplayblock.color], true);
	}
}

void Player::init(void)
{
	Btype[BL_T].pos.push_back({ VECTOR2(1, 1) ,VECTOR2(0, 1) ,VECTOR2(2, 1),VECTOR2(1, 0) });
	Btype[BL_T].pos.push_back({ VECTOR2(1, 1),VECTOR2(0, 1), VECTOR2(1, 2) ,VECTOR2(1, 0) });
	Btype[BL_T].pos.push_back({ VECTOR2(1, 1), VECTOR2(0, 1), VECTOR2(2, 1),VECTOR2(1, 2) });
	Btype[BL_T].pos.push_back({ VECTOR2(1, 1), VECTOR2(1, 0), VECTOR2(1, 2), VECTOR2(2, 1) });

	Btype[BL_L].pos.push_back({ VECTOR2(1, 1),VECTOR2(0, 1), VECTOR2(2, 1), VECTOR2(2, 0) });
	Btype[BL_L].pos.push_back({ VECTOR2(0, 0), VECTOR2(1, 0) ,VECTOR2(1, 1), VECTOR2(1, 2) });
	Btype[BL_L].pos.push_back({ VECTOR2(0, 1), VECTOR2(0, 0) , VECTOR2(1, 0) ,VECTOR2(2, 0) });
	Btype[BL_L].pos.push_back({ VECTOR2(1, 0), VECTOR2(1, 1) ,VECTOR2(1, 2), VECTOR2(2, 2) });

	Btype[BL_J].pos.push_back({ VECTOR2(1, 1), VECTOR2(0, 1), VECTOR2(2, 1), VECTOR2(0, 0) });
	Btype[BL_J].pos.push_back({ VECTOR2(1, 0),VECTOR2(1, 1),VECTOR2(1, 2), VECTOR2(0, 2) });
	Btype[BL_J].pos.push_back({ VECTOR2(0, 0), VECTOR2(1, 0), VECTOR2(2, 0), VECTOR2(2, 1) });
	Btype[BL_J].pos.push_back({ VECTOR2(2, 0),VECTOR2(1, 0), VECTOR2(1, 1), VECTOR2(1, 2) });

	Btype[BL_Z].pos.push_back({ VECTOR2(1, 1), VECTOR2(1, 0), VECTOR2(2, 1), VECTOR2(0, 0) });
	Btype[BL_Z].pos.push_back({ VECTOR2(1, 0), VECTOR2(1, 1), VECTOR2(0, 1),VECTOR2(0, 2) });

	Btype[BL_S].pos.push_back({ VECTOR2(1, 1),VECTOR2(0, 1),VECTOR2(2, 0),VECTOR2(1, 0)});
	Btype[BL_S].pos.push_back({ VECTOR2(0, 0), VECTOR2(0, 1), VECTOR2(1, 1), VECTOR2(1, 2) });

	Btype[BL_I].pos.push_back({ VECTOR2(2, 1),VECTOR2(1, 1), VECTOR2(0, 1), VECTOR2(3, 1) });
	Btype[BL_I].pos.push_back({ VECTOR2(1, 0),VECTOR2(1, 1), VECTOR2(1, 2),VECTOR2(1, 3) });

	Btype[BL_O].pos.push_back({ VECTOR2(1, 1), VECTOR2(0, 1) , VECTOR2(0, 0), VECTOR2(1, 0) });

}

Block Player::Random(void)
{
	Block blocks;
	blocks.RotaCnt = 0;
	blocks.color = GetRand(BL_MAX-1);
	for (auto pos : Btype[blocks.color].pos)
	{
		blocks.pos.push_back(pos);
	}
	return blocks;
}