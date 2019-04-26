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
	return true;
}


void SansenGamen::Update()
{
	if (GameStart == false) {
		if (Pad(0).IsTrigger(enButtonUp))
		{
			if (Kazu < MaxKazu)
			{
				Kazu++;
			}
			else if (Kazu > MaxKazu)
			{
				Kazu = MaxKazu;
			}
		}
		else if (Pad(0).IsTrigger(enButtonDown))
		{
			if (Kazu > MinKazu)
			{
				Kazu--;
			}
			else if (Kazu < MinKazu)
			{
				Kazu = MinKazu;
			}
		}
	}
	if (Pad(0).IsTrigger(enButtonA))
	{
		DeleteGO(this);
		GameStart = true;
		NewGO<Game>(0, "Game")->SetSanSenkazu(Kazu);
	}
}

void SansenGamen::PostRender(CRenderContext& rc) {
	if (Death == false) {
		wchar_t text[2506];

		swprintf_s(text, L"player %d\n", Kazu);
		m_font.Begin(rc);

		m_font.Draw(
			text,
			{ 0.0f, -250.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
		m_font.End(rc);
	}
}
