#include "stdafx.h"
#include "SetumeiGamen.h"
#include "Fade.h"

SetumeiGamen::SetumeiGamen()
{
}


SetumeiGamen::~SetumeiGamen()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_bgm);
}

bool SetumeiGamen::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Setumei1.dds", 1280.0f, 720.0f);
	m_push = NewGO<prefab::CSoundSource>(0);
	m_push->Init(L"sound/Kettei.wav");
	m_push->SetVolume(1.0f);

	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/sousa_setsumei.wav");
	m_bgm->Play(true);

	Fade::fadeOut();
	return true;
}

void SetumeiGamen::Update()
{
	if (Pad(0).IsTrigger(enButtonB) == true)
	{
		m_push->Play(false);
		Fade::fadeIn([&]() {
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		}, m_bgm);
	}
}