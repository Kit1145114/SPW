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
	MaxTimer -= GameTime().GetFrameDeltaTime();
	if (MaxTimer <= 0)
	{
		MaxTimer = 0.0f;
		m_game = FindGO<Game>("Game");
		m_game->SetGameMode(1);
	}
}
//‰æ–Ê‚É•`ŽÊ
void GamenTimer::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	swprintf_s(text, L"time%.0f", MaxTimer);
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
