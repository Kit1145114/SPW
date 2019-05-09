#include "stdafx.h"
#include "GamenDraw.h"
#include "GameWait.h"

GamenDraw::GamenDraw()
{
	m_push = NewGO<prefab::CSoundSource>(0);
	m_push->Init(L"sound/Kettei.wav");
}


GamenDraw::~GamenDraw()
{
	
}


void GamenDraw::Update()
{
	if (Pad(0).IsPress(enButtonUp) == true)
	{
		mode = 0;
	}
	else if (Pad(0).IsPress(enButtonDown) == true)
	{
		mode = 1;
	}

	if (mode == 0 && Pad(0).IsPress(enButtonA) == true){
		DeleteGO(this);
		m_push->Play(false);
#ifdef UseNetwork
		NewGO<GameWait>(1);
#else
		NewGO<SansenGamen>(1);
#endif
	}
	if (mode == 1 && Pad(0).IsPress(enButtonA) == true) {
		DeleteGO(this);
		m_push->Play(false);
		NewGO<SetumeiGamen>(0, "SetumeiGamen");
	}
}
//âÊñ Ç…ï`é ÅB
void GamenDraw::PostRender(CRenderContext& rc) {
	wchar_t text[2506];

	swprintf_s(text, L"game play\n");
	m_font.Begin(rc);

	if (mode == 0) {
		m_font.Draw(
			text,
			{ 0.0f, -105.0f },
			{ 0.0f, 1.0f, 1.0f, 1.0f },
			0.0f,
			1.25f
		);
	}
	else if (mode == 1) {
		m_font.Draw(
			text,
			{ 0.0f, -105.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.25f
		);
	}
	swprintf_s(text, L"Manual\n");
	if (mode == 0) {
		m_font.Draw(
			text,
			{ 0.0f, -200.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.25f
		);
	}
	else if (mode == 1) {
		m_font.Draw(
			text,
			{ 0.0f, -200.0f },
			{ 0.0f, 1.0f, 1.0f, 1.0f },
			0.0f,
			1.25f
		);
	}
	m_font.End(rc);
}