#include "stdafx.h"
#include "Draw_2P.h"


Draw_2P::Draw_2P()
{
}


Draw_2P::~Draw_2P()
{
	DeleteGO(m_spriteRender);
}

bool Draw_2P::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/2P.dds", 200.0f, 100.0f);
	m_spriteRender->SetPosition(m_position);
	return true;
}

void Draw_2P::Update()
{
	if (Death == true)
	{
		State = false;
	}
	if (/*m_game->GetPl1Death()*/Death == true && State == false)
	{
		m_spriteRender->Init(L"sprite/Gekitui.dds", 200.0f, 100.0f);
		timer++;
		State = true;
		if (timer == 180)
		{
			//m_game->SetPl1Death(false);
			Death = false;
			State = false;
			timer = 0;
		}
	}
	else if (Death == false)
	{
		m_spriteRender->Init(L"sprite/2P.dds", 200.0f, 100.0f);
	}
	m_spriteRender->SetPosition(m_position);
}