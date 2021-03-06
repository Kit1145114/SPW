#include "stdafx.h"
#include "Draw_Player.h"


Draw_Player::Draw_Player()
{
}


Draw_Player::~Draw_Player()
{
	DeleteGO(m_spriteRender);
}

bool Draw_Player::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(draw_P, yoko, tate);
	m_spriteRender->SetPosition(m_position);
	return true;
}

void Draw_Player::Update()
{
	if (Death == true)
	{
		State = false;
	}
	//死んでいる間だけ呼び続ける。
	if (Death == true &&State == false)
	{
		m_spriteRender->Init(L"sprite/Gekitui.dds", yoko, tate);
		timer += GameTime().GetFrameDeltaTime();
		State = true;
		if (timer > Limit)
		{
			Death = false;
			State = false;
			timer = 0.0f;
		}
	}
	//時間でプレイヤーの画像を差し替える。
	else if (Death == false && State == false)
	{
		m_spriteRender->Init(draw_P, yoko, tate);
		State = true;
	}
	m_spriteRender->SetPosition(m_position);
}