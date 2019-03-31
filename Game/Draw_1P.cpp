#include "stdafx.h"
#include "Draw_1P.h"


Draw_1P::Draw_1P()
{
}


Draw_1P::~Draw_1P()
{
	DeleteGO(m_spriteRender);
}

bool Draw_1P::Start()
{
	m_state = enState_1P;
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/1P.dds", 200.0f, 100.0f);
	m_spriteRender->SetPosition(m_position);
	return true;
}

void Draw_1P::Update()
{
	if (Death == true)
	{
		State = false;
	}
	if (/*m_game->GetPl1Death()*/Death == true &&State == false)
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
	else if (/*m_game->GetPl1Death()*/Death == false && State == false)
	{
		m_spriteRender->Init(L"sprite/1P.dds", 200.0f, 100.0f);
		State = true;
	}
	//if (m_state == enState_1P&&State == false)
	//{
	//	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//	m_spriteRender->Init(L"sprite/1P.dds", 200.0f, 100.0f);
	//	m_spriteRender->SetPosition(m_position);
	//	State = true;
	//	if (Death == true && State == true)
	//	{
	//		m_state = enState_Gekitui;
	//		m_spriteRender->SetPosition(m_position);
	//		State = false;
	//	}
	//}
	//else if (m_state == enState_Gekitui && State== false)
	//{
	//	m_spriteRender->Init(L"sprite/Gekitui.dds", 200.0f, 100.0f);
	//	State = true;
	//	if (Death == false && State == true)
	//	{
	//		m_state = enState_1P;
	//		State = false;
	//	}
	//}
	m_spriteRender->SetPosition(m_position);
}