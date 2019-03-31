#include "stdafx.h"
#include "Draw_3P.h"


Draw_3P::Draw_3P()
{
}


Draw_3P::~Draw_3P()
{
	DeleteGO(m_spriteRender);
}

bool Draw_3P::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/3P.dds", 200.0f, 100.0f);
	m_spriteRender->SetPosition(m_position);
	return true;
}

void Draw_3P::Update()
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
		m_spriteRender->Init(L"sprite/2P.dds", 200.0f, 100.0f);
	}
	m_spriteRender->SetPosition(m_position);
}