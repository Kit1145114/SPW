#include "stdafx.h"
#include "Draw_4P.h"


Draw_4P::Draw_4P()
{
}


Draw_4P::~Draw_4P()
{
	DeleteGO(m_spriteRender);
}

bool Draw_4P::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/4P.dds", 200.0f, 100.0f);
	m_spriteRender->SetPosition(m_position);
	return true;
}

void Draw_4P::Update()
{
	if (/*m_game->GetPl1Death()*/Death == true)
	{
		m_spriteRender->Init(L"sprite/Gekitui.dds", 200.0f, 100.0f);
		timer++;
		if (timer == 180)
		{
			//m_game->SetPl1Death(false);
			Death = false;
			timer = 0;
		}
	}
	else if (/*m_game->GetPl1Death()*/Death == false)
	{
		m_spriteRender->Init(L"sprite/4P.dds", 200.0f, 100.0f);
	}
	m_spriteRender->SetPosition(m_position);
}