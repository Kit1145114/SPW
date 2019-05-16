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
	if (Death == true &&State == false)
	{
		m_spriteRender->Init(L"sprite/Gekitui.dds", yoko, tate);
		timer++;
		State = true;
		if (timer == Limit)
		{
			Death = false;
			State = false;
			timer = 0;
		}
	}
	else if (Death == false && State == false)
	{
		m_spriteRender->Init(draw_P, yoko, tate);
		State = true;
	}
	m_spriteRender->SetPosition(m_position);
}