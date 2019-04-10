#include "stdafx.h"
#include "SansenKazu.h"


SansenKazu::SansenKazu()
{
}


SansenKazu::~SansenKazu()
{
}

bool SansenKazu::Start()
{
	return true;
}

void SansenKazu::Update()
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
		GameStart = true;
	}
}
void SansenKazu::PostRender(CRenderContext& rc) {
	if (Death == false) {
		wchar_t text[2506];

		swprintf_s(text, L"¡%d\n", Kazu);
		m_font.Begin(rc);

		m_font.Draw(
			text,
			{ 0.0f, -200.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
		m_font.End(rc);
	}
}