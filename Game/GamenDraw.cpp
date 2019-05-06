#include "stdafx.h"
#include "GamenDraw.h"


GamenDraw::GamenDraw()
{
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
		NewGO<SansenGamen>(1, "SansenGamen");
	}
	if (mode == 1 && Pad(0).IsPress(enButtonA) == true) {
		DeleteGO(this);
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
			{ 0.0f, -75.0f },
			{ 0.0f, 1.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
	}
	else if (mode == 1) {
		m_font.Draw(
			text,
			{ 0.0f, -75.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
	}
	swprintf_s(text, L"Manual\n");
	if (mode == 0) {
		m_font.Draw(
			text,
			{ 0.0f, -200.0f },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
	}
	else if (mode == 1) {
		m_font.Draw(
			text,
			{ 0.0f, -200.0f },
			{ 0.0f, 1.0f, 1.0f, 1.0f },
			0.0f,
			1.5f
		);
	}
	m_font.End(rc);
}