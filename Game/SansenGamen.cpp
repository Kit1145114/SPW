#include "stdafx.h"
#include "SansenGamen.h"


SansenGamen::SansenGamen()
{
}


SansenGamen::~SansenGamen()
{
	DeleteGO(m_spriteRender);
}

bool SansenGamen::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Sanka.dds", 1280.0f, 720.0f);
	s_kazu = NewGO<SansenKazu>(0, "SansenKazu");
	return true;
}


void SansenGamen::Update()
{
	if (Pad(0).IsTrigger(enButtonA))
	{
		DeleteGO(this);
		s_kazu->DeathCount(true);
		NewGO<Game>(0, "Game");
	}
}
