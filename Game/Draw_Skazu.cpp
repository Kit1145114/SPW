#include "stdafx.h"
#include "Draw_Skazu.h"


Draw_Skazu::Draw_Skazu()
{
}


Draw_Skazu::~Draw_Skazu()
{
}

void Draw_Skazu::Update()
{
}

void Draw_Skazu::PostRender(CRenderContext& rc)
{
	wchar_t text[256];

	swprintf_s(text, L"star%d", S_kazu);
	m_font.Begin(rc);

	m_font.Draw(
		text,
		{m_position},
		{Color},
		0.0f,
		1.0f
	);

	m_font.End(rc);
}
