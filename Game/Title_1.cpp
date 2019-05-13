#include "stdafx.h"
#include "Title_1.h"


Title_1::Title_1()
{
}


Title_1::~Title_1()
{
	DeleteGO(m_spriteRender);
}

bool Title_1::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title1.dds", 1280.0f, 720.0f);
	return true;
}

void Title_1::Update()
{
	m_timer++;
	if (m_timer == Limit)
	{
		DeleteGO(this);
		NewGO<Title_2>(0,"Title_2");
	}
}