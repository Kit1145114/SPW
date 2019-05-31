#include "stdafx.h"
#include "ResultDraw.h"

void ResultDraw::PostRender(CRenderContext& rc)
{
	if (!active) {
		return;
	}

	wchar_t text[20];
	if (Juni == 1) {
		swprintf_s(text, L"1th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -400.0f, 195.0f },
			{ 1.0f, 0.95f, 0.0f, 1.0f },
			0.0f,
			1.675f
		);
	}
	else if (Juni == 2)
	{
		swprintf_s(text, L"2th\n");
		m_font.Begin(rc);
		m_font.Draw(
		text,
		{ -400.0f, 55.0f },
		{ 0.9f, 0.9f, 0.9f, 1.0f },
			0.0f,
			1.675f
			);
	}
	else if (Juni == 3) {
		swprintf_s(text, L"3th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -400.0f, -95.0f },
			{ 1.0f, 0.2f, 0.0f, 1.0f },
			0.0f,
			1.675f
		);
	}
	else if (Juni == 4) {
		swprintf_s(text, L"4th\n");
		m_font.Begin(rc);
		m_font.Draw(
			text,
			{ -400.0f, -245.0f },
			{ 0.75f, 0.0f, 0.75f, 1.0f },
			0.0f,
			1.675f
		);
	}
	m_font.End(rc);
}