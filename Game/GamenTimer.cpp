#include "stdafx.h"
#include "GamenTimer.h"


GamenTimer::GamenTimer()
{
}


GamenTimer::~GamenTimer()
{
}

void GamenTimer::Update()
{
	if (MaxTimer == 0)
	{
		m_game = FindGO<Game>("Game");
		m_game->SetGameMode(1);
	}
}
//‰æ–Ê‚É•`ŽÊ
void GamenTimer::PostRender(CRenderContext& rc)
{
	m_timer++;
	if (m_timer == 60)
	{
		MaxTimer--;
		m_timer = 0;
	}

	wchar_t text[256];	int sec = (int)m_timer % 60;
	swprintf_s(text, L"TIME%d", MaxTimer);
	m_font.Begin(rc);

	m_font.Draw(
		text,
		{ -550.0f, 300.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		0.0f,
		1.5f
	);
	m_font.End(rc);
}
