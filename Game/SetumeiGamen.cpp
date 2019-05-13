#include "stdafx.h"
#include "SetumeiGamen.h"
#include "Fade.h"

SetumeiGamen::SetumeiGamen()
{
}


SetumeiGamen::~SetumeiGamen()
{
	DeleteGO(m_spriteRender);
}

bool SetumeiGamen::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Setumei1.dds", 1280.0f, 720.0f);
	m_push = NewGO<prefab::CSoundSource>(0);
	m_push->Init(L"sound/Kettei.wav");

	Fade::fadeOut();
	return true;
}

void SetumeiGamen::Update()
{
	Kirikae();
	switch (mode)
	{
	case 0:
		m_spriteRender->Init(L"sprite/Setumei1.dds", 1280.0f, 720.0f);
		break;
	case 1:
		m_spriteRender->Init(L"sprite/Setumei2.dds", 1280.0f, 720.0f);
		break;
	}
}

void SetumeiGamen::Kirikae()
{
	if (Pad(0).IsPress(enButtonLeft) == true)
	{
		mode = 0;
	}
	if (Pad(0).IsPress(enButtonRight) == true)
	{
		mode = 1;
	}
	if (Pad(0).IsTrigger(enButtonB) == true)
	{
		Fade::fadeIn([&]() {
			m_push->Play(false);
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		});
	}
}