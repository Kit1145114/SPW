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
	m_push->SetVolume(0.5f);

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
	case 2:
		m_spriteRender->Init(L"sprite/Setumei3.dds", 1280.0f, 720.0f);
		break;
	}
}

void SetumeiGamen::Kirikae()
{
	if (Pad(0).IsTrigger(enButtonLeft) == true)
	{
		mode--;
		if (mode < 0)
		{
			mode = 0;
		}
	}
	if (Pad(0).IsTrigger(enButtonRight) == true)
	{
		mode++;
		if (mode > 2)
		{
			mode = 2;
		}
	}
	if (Pad(0).IsTrigger(enButtonB) == true)
	{
		m_push->Play(false);
		Fade::fadeIn([&]() {
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		});
	}
}