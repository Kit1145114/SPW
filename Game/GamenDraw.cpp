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
	if (Pad(0).IsPress(enButtonA) == true)
	{
		DeleteGO(this);
	}
}
//âÊñ Ç…ï`é ÅB
void GamenDraw::PostRender(CRenderContext& rc) {
	wchar_t text[2506];

	swprintf_s(text, L"Å`PLEASE EN BUTTONÅ`\n");
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