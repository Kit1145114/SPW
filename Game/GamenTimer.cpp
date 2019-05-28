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
	if (Game::GetInstance()->isWait())return;
	if (MaxTimer == 0)
	{
		m_game = FindGO<Game>("Game");
		m_game->SetGameMode(1);
	}
	m_timer++;
	if (m_timer == frame) {
		MaxTimer--;
		m_timer = 0;
	}
}
//‰æ–Ê‚É•`ŽÊ
void GamenTimer::PostRender(CRenderContext& rc)
{
	wchar_t text[256];	int sec = (int)m_timer % 60;
	swprintf_s(text, L"time%d", MaxTimer);
	m_font.Begin(rc);

	m_font.Draw(
		text,
		{ -630.0f, 320.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		0.0f,
		1.5f,
		{0.0f, 0.5f}
	);

	m_font.End(rc);
}
