#include "stdafx.h"
#include "Title_2.h"
#include "GameWait.h"

Title_2::Title_2()
{
}


Title_2::~Title_2()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_Draw);
}

bool Title_2::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title_A.dds", 1280.0f, 720.0f);
	m_Draw = NewGO<GamenDraw>(0, "GamenDraw");
	return true;
}

void Title_2::Update()
{
	if (Pad(0).IsPress(enButtonA) == true)
	{
		DeleteGO(this);
		//NewGO<SansenGamen>(0,"SansenGamen");
		NewGO<GameWait>(0)->Init();
	}
}